#ifndef N4S_API_CONFIG_H_
# define N4S_API_CONFIG_H_

#ifndef NAME_LENGTH
#define NAME_LENGTH (255)
#endif

#ifndef IN_IO
#define IN_IO(io) ((((io_t *)io)->same) ? ((io_t *)io)->out : ((io_t *)io)->in)
#endif

#endif /* !N4S_API_CONFIG_H_ */
