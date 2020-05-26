# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <argp.h>

bool is_valid_url(char *url) {
    return false;
}

bool is_url_in_db(char *url) {
    return false;
}

int add_url(char *url){
    return EXIT_FAILURE;
}

// Notice that there is no visible call to this function.
// This is because `parse_opt` is a __callback function__.
// Instead `Argp` is calling this function on our behalf when it processes
// the `argc` and `argv` that we pass to `argp_parse`.
// `Argp` repeatedly calls this function for eveyr option and argument
// on the command line.
//
// The signature for the callback is defined it accepts is defined by `Argp`
// Function Arguments:
//   key:   An option's unique key, which can be the short option.
//          We can also use non-character keys.
//   arg:   The option argument's value, as a string.
//   state: This keeps Argp's state as we iterate the callback function
static int parse_opt (int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'a': {
            if (!is_valid_url(arg)){
                argp_failure(state, 1, 0, "invalid URL");
            }
            if (is_url_in_db(arg)) {
                argp_failure(state, 1, 0, "URL already added");
            }
            // TODO: If it already exists, don't add it again
            printf("selected %s", arg);
            break;
        }
    }

    return EXIT_SUCCESS; // EXIT_FAILURE will stop Argp and return FAILURE
}


int main(int argc, char **argv) {

    struct argp_option options[] = {
        // Field options:
        //   1st -> long
        //   2nd -> short
        //   3rd -> name of the argument to this option
        //   4th -> A set of flags that change how our option works
        //   5th -> "Description of the option to be shown on help"
        { "add", 'a', "URL", 0, "Add an URL that you have downloaded from" },
        { "check",
          'c',
          "URL",
          0 ,
          "check if you have aleardy downloaded from this URL" },
        { 0 }
    };

    // This is the most important struct here
    // options: All of our cli options
    // parse_opt: A pointer to a function that Argp will call to assist in
    //            parsing our options
    //
    //            We can just use the name of the function to assign the
    //            pointer to where the function is in memory. This is similar
    //            to how the name of an array is a pointer to the array's first
    //            element.
    struct argp argp = {options, parse_opt};

    return argp_parse(&argp, argc, argv, 0, 0, 0);
    /* return EXIT_SUCCESS; */
}

