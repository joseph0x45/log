#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define LOG_HOME_DIR ".log_home"
#define DATE_SIZE 11
#define TIME_SIZE 9

void print_usage(void);

char *get_log_home(void);

int log_entry(char *title, char *content);

void get_current_date_time(char *date_out, size_t date_size, char *time_out,
                           size_t time_size);

int main(int argc, char **argv) {
  if (argc == 3) {
    return log_entry(argv[1], argv[2]);
  }
  print_usage();
  return 0;
}

void print_usage(void) { printf("log <title> <content>\n"); }

char *get_log_home(void) {
  static char log_home[PATH_MAX];
  char *user_home = getenv("HOME");
  if (!user_home) {
    fprintf(stderr, "Error: Could not get log home: HOME is not set\n");
    return NULL;
  }
  snprintf(log_home, sizeof(log_home), "%s/%s", user_home, LOG_HOME_DIR);
  struct stat s = {0};
  if (stat(log_home, &s) == -1) {
    if (mkdir(log_home, 0700) == -1) {
      perror("Error: Could not get log home: ");
      return NULL;
    }
  }
  return log_home;
}

void get_current_date_time(char *date_out, size_t date_size, char *time_out,
                           size_t time_size) {
  time_t now = time(NULL);
  struct tm *time_info = localtime(&now);
  if (date_out && date_size > 0) {
    strftime(date_out, date_size, "%Y-%m-%d", time_info);
  }
  if (time_out && time_size > 0) {
    strftime(time_out, time_size, "%H:%M:%S", time_info);
  }
}

int log_entry(char *title, char *content) {
  if (strcmp(title, "") == 0 || strcmp(content, "") == 0) {
    print_usage();
    return 1;
  }
  char current_date[DATE_SIZE], current_time[TIME_SIZE];
  get_current_date_time(current_date, sizeof(current_date), current_time,
                        sizeof(current_time));
  char log_file_path[PATH_MAX];
  char *log_home = get_log_home();
  snprintf(log_file_path, sizeof(log_file_path), "%s/%s.log", log_home,
           current_date);
  FILE *f = fopen(log_file_path, "a");
  if (!f) {
    fprintf(stderr, "Error: Could not open log file at %s", log_file_path);
    perror("");
    return 1;
  }
  fprintf(f, "[%s] %s: %s\n", current_time, title, content);
  fclose(f);
  return 0;
}
