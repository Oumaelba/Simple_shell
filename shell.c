#include "shell.h"

int prompt(void)
{
  char *prompt = "(Bstshell) $ ";
  int n = 0;
  
  n = write(STDOUT_FILENO, prompt, _strlen(prompt));
  return (0);
}

int        length_of_paths(char *path, char *del)
{
    int        length;
    char        *line, *copied_path;
    length = 0;
    copied_path = strdup(path);
    line = strtok(copied_path, del);
    while (line)
    {
        length++;
        line = strtok(NULL, del);
    }
    free(copied_path);
    return (length);
}

int magic(char *input, ssize_t size)
{
  char *path_cmd = NULL, *g_path = NULL;
  char **d_str = NULL, **paths = NULL;
  int exit_code = 0;

  if (input[size - 1] == '\n')
      input[size - 1] = '\0'; 
  d_str = parse(input);

  if (d_str == NULL || *d_str == NULL || **d_str == '\0')
  {
    free(input);
    free_buff(d_str);
    return (0);
  }
  if (strcmp(d_str[0], "exit") == 0)
  {
    free(input);
    free_buff(d_str);
    //free_buff(paths);
    return (-1);
  }
  else if (strcmp(d_str[0], "cd") == 0)
  {
    free(input);
    cd_cmd(d_str);
  }
  g_path = _strdup(bring_path("PATH"));
  if (!g_path)
  {
    free(g_path);
    return (-1);
  }
  
  paths = pathing(g_path);
  if (!paths)
  {
    free(g_path);
    free(input);
    free_buff(d_str);
    return (-1);
  }
  path_cmd = check_path(paths, d_str[0]);
  free_buff(paths);
  //free(input);
  if (!path_cmd)
  {
    free(input);
    free_buff(d_str);
    free_buff(paths);
    free(g_path);
    printf("path_cmd ");
    return (-1);
  }
  else if (exit_code == 0)
  {
    exit_code = execution(d_str, path_cmd);
    free_buff(d_str);
    //free_buff(paths);
    free(g_path);
    free(path_cmd);
    return (0);
  }
  printf("Hello world\n");
  //free(path_cmd);
  for (int i = 0; d_str[i] != NULL; i++)
        printf("\nd_str[%d]: %s\n", i, d_str[i]);
}
int main(int ac, char **av, char **env)
{
  size_t buff = 0;
  ssize_t s_read = 0;
  int pokemon = 1;
  char *str = NULL;
  int exit_code = 0;

  while (pokemon)
  {
    
    prompt();
    fflush(stdout);
    if ((s_read = getline(&str, &buff, stdin)) == EOF) 
    {
      free(str);
      printf("\n");
      printf("exit\n");
      return (-1);
    }
    exit_code = magic(str, s_read);
    if (exit_code == -1)
    {
      free(str);
      printf("exit\n");
      return (-1);
    }
  }
  free(str);
  return (0);
}
