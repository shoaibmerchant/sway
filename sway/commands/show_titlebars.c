#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include "sway/commands.h"
#include "sway/config.h"
#include "sway/output.h"
#include "sway/tree/arrange.h"
#include "log.h"
#include "util.h"

struct cmd_results *cmd_show_titlebars(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "show_titlebars", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	config->show_titlebars = parse_boolean(argv[0], config->show_titlebars);

	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		arrange_workspace(output_get_active_workspace(output));
		output_damage_whole(output);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}
