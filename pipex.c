#include "pipex.h"

void last_free(t_ppx *ppx) {
	
    int	i = 0;

	free_array(ppx->value_splitted);

	while (i < 2)
		free(ppx->cmd_path[i++]);
	free(ppx->cmd_path);

	i = 0;
	while (ppx->cmd_args[i])
		free_array(ppx->cmd_args[i++]);
	free(ppx->cmd_args);

	free(ppx);
}

void create_fds(t_ppx *ppx, char *argv[]) {

    ppx->in = open(argv[1], O_RDONLY);
    ppx->out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (ppx->in < 0 || ppx->out < 0) {
        printf("%s\n", "Error occurred while executing the file");
        exit(EXIT_FAILURE);
    }
}

void save_path_value(t_ppx *ppx, char *envp[]) {

    int search_path = 1;
    char path_var[255] = "", value[255] = "";
    char *kv_pair = NULL;

    for (int i = 0; envp[i]; i++) {

        if (strncmp(envp[i], "PATH=", 5) == 0) {

            search_path = 0;
            strcpy(path_var, envp[i]);
            kv_pair = strtok(path_var, "=");

            for (int j = 0; kv_pair; j++) {

                if (j == 1)
                    strcpy(value, kv_pair);

                kv_pair = strtok(NULL, "=");
            }
        }
    }

    if (search_path == 1) {
        printf("%s\n", "Error accessing a variable PATH");
        exit(EXIT_FAILURE);
    }

    ppx->value_splitted = ft_split(value, ':'); 

}

void access_check(t_ppx *ppx, char *argv[]) {

    int accessable = 0;

    for (int i = 0; i < 2; i++) {

        ppx->cmd_args[i] = ft_split(argv[i + 2], ' ');
        char *cmd = ppx->cmd_args[i][0];

        for (int j = 0; ppx->value_splitted[j]; j++) {
            
            ppx->cmd_path[i] = ft_strjoin(ppx->value_splitted[j], '/', cmd);  
            if (access(ppx->cmd_path[i], X_OK) == 0) {
                accessable = 1;
                break ;
            }
            free(ppx->cmd_path[i]);
        }

        if (accessable == 0) {
            printf("%s\n", "Invalid command!");
            free_array(ppx->value_splitted);
            while (i--)
				free_array(ppx->cmd_args[i]);
            exit(EXIT_FAILURE);
        }
    }
}

void execute_cmds(t_ppx *ppx, char *envp[]) {
    
    int end[2];
    pid_t proc; // will soon be forked ;)

    if (pipe(end) < 0) {
		printf("%s\n", "Error occurred while creating a pipe");
		exit(EXIT_FAILURE);
	}
    
    for (int i = 0; i < 2; i++) {

        if (i == 0) {
            dup2(ppx->in, STDIN_FILENO); // we want argv[1] to be execve() input
            close(ppx->in); 
        }
        else {
            dup2(end[0], STDIN_FILENO); // end[0] becomes cmd2 stdin
            close(end[0]); 
        }

        if (i == 0) 
            dup2(end[1], STDOUT_FILENO); // end[1] becomes cmd1 stdout
        else
            dup2(ppx->out, STDOUT_FILENO); // we want argv[4] to be execve() stdout
        
        proc = fork();
        if (proc == 0) // if fork() returns 0, we are in the child process
            execve(ppx->cmd_path[i], ppx->cmd_args[i], envp);
        else {
		    close(end[1]);
		    waitpid(proc, NULL, 0); // blocks the parent process until the child has finished
	    }
    }
}

int main(int argc, char *argv[], char *envp[]) {

    t_ppx *ppx;
    ppx = malloc(sizeof(t_ppx));
    ppx->cmd_args = malloc(sizeof(char **) * 3);
    ppx->cmd_path = malloc(sizeof(char *) * 3);

    if (argc != 5) {
        printf("%s\n", "Incorrect number of arguments!");
        exit(EXIT_FAILURE);
    }

    create_fds(ppx, argv);
    save_path_value(ppx, envp);
    access_check(ppx, argv);
    execute_cmds(ppx, envp);
    last_free(ppx);

    return 0;
} 