
#include "fstream"
#include "vector"

#include "src/values/value_f.h"
//#include "block_stream.h"

#include "src/io/block_writer.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

using namespace std;


int repeat = 1000000;

struct prop_desc_t {
    int represent;
    vs::type_desc_t type;
};

unordered_map<string, shared_ptr<prop_desc_t>> props = std::unordered_map<std::string, shared_ptr<prop_desc_t>>({
    {"id", shared_ptr<prop_desc_t>(new prop_desc_t({ 6, vs::NUMBER })) },
    {"firstName", shared_ptr<prop_desc_t>(new prop_desc_t({ 1, vs::STRING })) },
    {"lastName", shared_ptr<prop_desc_t>(new prop_desc_t({ 2, vs::STRING }))},
    {"yob", shared_ptr<prop_desc_t>(new prop_desc_t({ 3, vs::NUMBER }))},
    {"address", shared_ptr<prop_desc_t>(new prop_desc_t({ 4, vs::OBJECT }))},
    {"is_married", shared_ptr<prop_desc_t>(new prop_desc_t({ 5, vs::BOOLEAN }))},
    {"list", shared_ptr<prop_desc_t>(new prop_desc_t({ 7, vs::LIST }))},
});

unordered_map<int, shared_ptr<prop_desc_t>> schemas = unordered_map<int, shared_ptr<prop_desc_t>> ({
    {6, props["id"]},
    {1, props["firstName"]},
    {2, props["lastName"]},
    {3, props["yob"]},
    {4, props["address"]},
    {5, props["is_married"]},
    {7, props["list"]}
});

void exe_write() {

    ofstream writer ("data.bin", ios::out | ios::binary);

    vs::block_writer stream(512 + 128);

    vs::upair_t record = unordered_map<string, vs::value_t*>({
        {"firstName", vs::value_f::create("Johnathan")},
        {"lastName", vs::value_f::create("Smith")},
        {"yob", vs::value_f::create(1987)},
        {"address", vs::value_f::create(
            unordered_map<string, vs::value_t*>({
                {"unit", vs::value_f::create(32)},
                {"street", vs::value_f::create("magrid str")},
                {"suburd", vs::value_f::create("marrick")}
            })
        )},
        {"is_married", vs::value_f::create(false)},
        {"list", vs::value_f::create(vector<vs::value_t*>({
            vs::value_f::create("next is num"),
            vs::value_f::create(45),
            vs::value_f::create("then bool"),
            vs::value_f::create(true)
        }))}
    });

    if (writer.is_open()) {
    
        int i = 0;
        while (i++ < repeat) {


            record["id"] = vs::value_f::create(i);
            
            for (auto itr: record) {

                stream.append(props[itr.first]->represent);
                
                itr.second->assign(&stream);
            }
            
            stream.write(&writer);

        };
        
        writer.close();
     }
}

void read_obj(vs::upair_t* rs,
              int num_of_items,
              size_t* pos,
              char* fmap) {
    
    char* name, *buff;
    int pi = 0;
    size_t ibp;
    
    while (num_of_items-- > 0) {
        name = new char[25];
        pi = 0;
        ibp = *pos;
        
        while (fmap[ibp] != '\0') {
            name[pi++] = fmap[ibp++];
        }
        name[pi] = '\0';
        ibp = *pos + 24;
        
        switch (static_cast<vs::type_desc_t>(fmap[ibp])) {
                
            case vs::STRING: {
                ibp += 4;
                
                int size = (int&)fmap[ibp], buff_pos = 0;
            
                ibp += 4;
                buff = new char[size + 1];
                
                while (fmap[ibp] != '\0'){
                    buff[buff_pos++] = fmap[ibp++];
                }
                
                buff[buff_pos] = '\0';
                
                ibp += 55 - buff_pos;
                (*rs)[name] = vs::value_f::create(buff);
                
                break;
            }
            case vs::NUMBER: {
                
                ibp += 4;
                
                (*rs)[name] = vs::value_f::create((double long&)fmap[ibp]);
                
                ibp += 16;
                break;
            }
            case vs::BOOLEAN: {
                
                ibp += 4;
                
                (*rs)[name] = vs::value_f::create((bool&)fmap[ibp]);
                ibp += 1;
                
                break;
            }
        }
        
        *pos = ibp;
        
    }
    
}

void read_list(vector<vs::value_t*>* rs,
               int num_of_items,
               size_t* pos,
               char* fmap) {
    char* buff;
    size_t ibp = *pos;
    int size, buff_pos;
    long double number = 0;
    
    while (num_of_items-- > 0) {
        
        switch (static_cast<vs::type_desc_t>(fmap[ibp])) {
                
            case vs::STRING: {
                ibp += 4;
                
                size = (int&)fmap[ibp];
                buff_pos = 0;
                
                ibp += 4;
                buff = new char[size+1];
                
                while (fmap[ibp] != '\0'){
                    buff[buff_pos++] = fmap[ibp++];
                }
                
                buff[buff_pos] = '\0';
                
                ibp += 55 - buff_pos;
                
                rs->push_back(vs::value_f::create(buff));
                
                delete[] buff;
                
                break;
            }
            case vs::NUMBER: {
                
                ibp += 4;
                
            
                buff = reinterpret_cast<char*>(&number);
//                std::copy(&fmap[ibp], &fmap[ibp] + sizeof(double long), buff);
                std::memcpy(buff, &fmap[ibp], 16);
                rs->push_back(vs::value_f::create(number));
                
                ibp += 16;
                
                break;
            }
            case vs::BOOLEAN: {
                
                ibp += 4;
                rs->push_back(vs::value_f::create((bool&)fmap[ibp]));
                ibp += 1;
                
                break;
            }
        }
        
    }
    
    
    *pos = ibp;
}

void exe_read() {

    string path = "data.bin";
    size_t f_size;
    char* fmap = nullptr;
    bool opening = false;

    int fd = open(path.c_str(), O_RDONLY, (mode_t)0600);

    // mmap file start to end (allows null chars)
    off_t pos = lseek(fd, 0, SEEK_CUR);
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, pos, SEEK_SET);

    if (size == 0)
    {
        close(fd);
        f_size = -1;
    }
    else
    {
        int prot = PROT_READ;
        int flags = MAP_SHARED;

        void *ptr;
        int pagesize = getpagesize();
        if (size % pagesize != 0)
        {

            ptr = mmap(NULL, size + 1, prot, flags, fd, 0);
        }
        else
        {
            size_t fullsize = size + pagesize;

            ptr = mmap(NULL, fullsize, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
            ptr = mmap(ptr, fullsize, prot, flags | MAP_FIXED, fd, 0);
        }

        if (ptr == MAP_FAILED)
        {
            close(fd);
            f_size = -1;
        }
        else
        {
            f_size = size;
            fmap = (char *)ptr;
            opening = true;
        }
    }

    if (opening) {
        size_t pos = 0;
        
        string str;
        int type, size, buff_pos, number_of_items;
        size_t i;
        char* buff;
        char name[25];
        
        shared_ptr<prop_desc_t> ptype;
        
        bool bool_v;
        double long number_v;
        
        while (fmap[pos] != '\0' && pos < 512) {
            type = (int&)fmap[pos];
            ptype = schemas[type];
            
            pos += 4;
            
            switch(ptype->type) {
                    
                case vs::STRING:
                    
                    size = (int&)fmap[pos];
                    pos += 4;
                    i = pos;
                    buff_pos = 0;
                    buff = new char[size + 1];
                    while (fmap[i] != '\0') {
                        buff[buff_pos++] = fmap[i++];
                    }
                    buff[buff_pos] = '\0';
                    pos += 55;
                    
                    break;
                
                case vs::BOOLEAN:
                    
                    bool_v = (bool&)fmap[pos];
                    
                    pos ++;
                    break;

                case vs::NUMBER:
                    
                    number_v = (double long&)fmap[pos];
                    
                    pos += 16;
                    break;
                    
                case vs::OBJECT: {
                    
                    number_of_items = (int&)fmap[pos];
                    vs::upair_t rs;
                    rs.reserve(number_of_items);
                    
                    pos += 4;
                    read_obj(&rs, number_of_items, &pos, fmap);
                    
                    break;
                }
                case vs::LIST:
                    
                    
                    number_of_items = (int&)fmap[pos];
                    vector<vs::value_t*> rsv;
                    
                    pos += 4;
                    read_list(&rsv, number_of_items, &pos, fmap);
                    
                    break;

            }
        }

        munmap(fmap, f_size);
    }
    close(fd);
    
}

int main (int no, char* args[]) {

//   exe_write();

     exe_read();

    // TODO:
    // 1. Make description, precalculate start and end position for indexes on startup
    //      + If len of index is greater than left over space (index.size() > block_len_left), go to next block
    // 2. When writing, use precalculated position (start and end) for key and indexes
    
    return 0;
}
