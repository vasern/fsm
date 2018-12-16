
#include "src/fsm.h"
#include "src/values/value_f.h"

int main(int count, char* args[]) {
    
    vs::layout_t sc = vs::layout_t({
        vs::col_t("id", vs::STRING, 32),
        vs::col_t("firstName", vs::STRING, 55),
        vs::col_t("lastName", vs::STRING, 55),
        vs::col_t("yob", vs::NUMBER),
        vs::col_t("is_married", vs::BOOLEAN)
    }, 1024);
    
    vs::upair_t record({
        {"id", vs::value_f::create("random_key_num_2")},
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
    
    
    
//    vs::collect_t db(".", "db", sc, true);
//    db.open_writer();
    
//    // Perform Single Write
//    db.insert(&record);
    
//    db.close_writer();
    
    // Perform Filter
//    vs::upair_t query = {{ "id", vs::value_f::create("random_key_num_2") }};
//    std::vector<vs::block_reader*> results = db.filter(&query);
//
//    db.open_reader();
//    auto object = results[0]->object();
//    db.close_reader();
    
    std::unordered_map<std::string, vs::layout_t> tables = std::unordered_map<std::string, vs::layout_t>({
        { "Users" , vs::layout_t({
                vs::col_t("id", vs::STRING, 32),
                vs::col_t("firstName", vs::STRING, 55),
                vs::col_t("lastName", vs::STRING, 55),
                vs::col_t("yob", vs::NUMBER),
                vs::col_t("is_married", vs::BOOLEAN)
            }, 1024)
        },
        { "TodoItems", vs::layout_t({
                vs::col_t("id", vs::STRING, 32),
                vs::col_t("name", vs::STRING, 55),
                vs::col_t("status", vs::BOOLEAN)
            }, 1024)
        }
    });
    vs::fsm fsm = vs::fsm(".");
//    fsm.setup(tables);
    
    auto Users = fsm.select("Users");
    return 0;
}
