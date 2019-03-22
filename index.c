#include "database.h"
#include "sqlite.h"
#include "server.h"

int main()
{
    database_config_t config = {
        .driver = "sqlite",
        .path = "./test.db",
        .verbose = true
    };

    database_instance_t* instance = create_sqlite_instance(config);
    instance->initialize_database(instance);

    database_table_t* table = add_table(instance, "testtable");
    database_field_t* field = add_table_field(table, "testfield", "TEXT");

    prepare_create_table(instance, table);

    instance->async_execute_sql(instance, instance->prepared_statement);

    free_instance(instance);

   //isten_and_serve("tcp://127.0.0.1:5560");
};
