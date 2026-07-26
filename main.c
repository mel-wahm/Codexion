#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	conf;
	int			valid;

	valid = 0;
	memset(&conf, 0, sizeof(t_config));
	valid = full_checker(argc, argv, &conf);
	if (valid)
		return (ft_perror(valid), valid);
	valid = initialize_data(&conf);
	if (valid)
		return (ft_perror(valid), valid);
	// valid = run_simulation(&conf);
	conf.start_time = current_time();
	for (int i = 0; i < conf.number_of_coders; i++)
		taking_dongle(&conf.coders[i], &conf);
	return (ft_perror(valid), clean_data(&conf), valid);
}
