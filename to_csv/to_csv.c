#include "readstat.h"

int handle_info(int obs_count, int var_count, void *ctx) {
    int *my_var_count = (int *)ctx;

    *my_var_count = var_count;

    return 0;
}

int handle_variable(int index,
		    readstat_variable_t *variable, 
		    const char *val_labels,
		    void *ctx)
{
    int *my_var_count = (int *)ctx;

    printf("%s", readstat_variable_get_name(variable));
    if (index == *my_var_count - 1) {
        printf("\n");
    } else {
        printf("\t");
    }

    return 0;
}

int
handle_value(int obs_index,
	     int var_index,
	     readstat_value_t value,
	     /* readstat_types_t type, */
	     void *ctx)
{
    int *my_var_count = (int *)ctx;
    if (!readstat_value_is_missing(value)) {
      /*
        if (type == READSTAT_TYPE_STRING) {
            printf("%s", readstat_string_value(value));
        } else if (type == READSTAT_TYPE_CHAR) {
            printf("%hhd", readstat_char_value(value));
        } else if (type == READSTAT_TYPE_INT16) {
            printf("%hd", readstat_int16_value(value));
        } else if (type == READSTAT_TYPE_INT32) {
            printf("%d", readstat_int32_value(value));
        } else if (type == READSTAT_TYPE_FLOAT) {
            printf("%f", readstat_float_value(value));
        } else if (type == READSTAT_TYPE_DOUBLE) {
            printf("%lf", readstat_double_value(value));
        }
      */
    }
    if (var_index == *my_var_count - 1) {
        printf("\n");
    } else {
        printf("\t");
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int my_var_count;
    readstat_error_t error;
    readstat_parser_t *parser;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    my_var_count = 0;
    error = READSTAT_OK;
    parser = readstat_parser_init();

    readstat_set_info_handler(parser, &handle_info);
    readstat_set_variable_handler(parser, &handle_variable);
    readstat_set_value_handler(parser, &handle_value);

    error = readstat_parse_sas7bdat(parser, argv[1], &my_var_count);

    readstat_parser_free(parser);

    if (error != READSTAT_OK) {
        printf("Error processing %s: %d\n", argv[1], error);
        return 1;
    }
    return 0;
}
