
#include "src/io/writer_t.h"
#include "src/io/reader_t.h"
#include "src/values/value_f.h"
#include "src/layout.h"


int main(int nargs, char* args[]) {
//
//    vs::descript_t props({
//        {"id", vs::prop_desc_t({ 6, vs::NUMBER }) },
//        {"firstName", vs::prop_desc_t({ 1, vs::STRING}) },
//        {"lastName", vs::prop_desc_t({ 2, vs::STRING }) },
//        {"yob", vs::prop_desc_t({ 3, vs::NUMBER }) },
//        {"address", vs::prop_desc_t({ 4, vs::OBJECT }) },
//        {"is_married", vs::prop_desc_t({ 5, vs::BOOLEAN }) },
//        {"list", vs::prop_desc_t({ 7, vs::LIST }) },
//    });
    
    
//    std::unordered_map<int, std::string> schemas({
//        {6, "id"},
//        {1, "firstName"},
//        {2, "lastName"},
//        {3, "yob"},
//        {4, "address"},
//        {5, "is_married"},
//        {7, "list"}
//    });
//
    
//    vs::block_desc_t block { 512 };
    //  vs::writer_t writer("./data.bin", &props, &block);
    
    vs::layout_t sc = vs::layout_t({
        vs::col_t("id", vs::STRING, 32),
        vs::col_t("firstName", vs::STRING, 55),
        vs::col_t("lastName", vs::STRING, 55),
        vs::col_t("yob", vs::NUMBER),
        vs::col_t("is_married", vs::BOOLEAN)
    }, 1024);

    vs::upair_t record({
        {"id", vs::value_f::create("random_key_num")},
        {"firstName", vs::value_f::create("Johnathan")},
        {"lastName", vs::value_f::create("Smith")},
        {"yob", vs::value_f::create(1987)},
        {"address", vs::value_f::create(
                                        std::unordered_map<std::string, vs::value_t*>({
            {"unit", vs::value_f::create(32)},
            {"street", vs::value_f::create("magrid str")},
            {"suburd", vs::value_f::create("marrick")}
        })
                                        )},
        {"is_married", vs::value_f::create(true)},
        {"list", vs::value_f::create(std::vector<vs::value_t*>({
            vs::value_f::create("next is num"),
            vs::value_f::create(45),
            vs::value_f::create("then bool"),
            vs::value_f::create(true)
        }))}
    });

    int i = 0, repeat = 1000000;
    
   std::string key;
   std::ofstream file ("./data.bin", std::ios::binary);

    while (i++ < repeat) {
//        sc.build(&record);
//        sc.write(&file);
    }
    file.close();
    
//    vs::reader_t reader("./data.bin", &sc);
//    vs::block_reader buff = reader.get(0);
//     vs::upair_t r_b;
//    while (i++ < repeat) {
//        r_b.clear();
//        r_b = buff.tags();

//        buff.next();
//    }

//    reader.close_conn();
    
    
    return 0;
}
