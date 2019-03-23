#include "database.h"
#include "sqlite.h"
#include "server.h"
#include "jsonapi.h"

void interrupt_handler(int dummy)
{
    exit(1);
}

int main()
{
    signal(SIGINT, interrupt_handler);
    /*
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
    */

    listen_and_serve("tcp://127.0.0.1:5560", serve_database_interface);

    /*
    database_instance_t *instance = parse_initialization_request("{ \"path\": \"./test.db\", \"driver\": \"sqlite\", \"tables\": \
        [{  \"name\": \"testtable\", \"fields\": [{ \"name\": \"testfield\", \"data_type\": \"TEXT\" }] }] }");

    puts(instance->config.path);

    database_table_t *test_table = (database_table_t *)instance->tables->item;

    create_table(instance, test_table);
    */
};
