/*
 *       daemon.h
 */

void log_message(char *filename,char *message);
void signal_handler(int sig);
void daemonize();
