#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

typedef struct node
{
    char *name;
    char *priority;
    int year;
    int month;
    int day;
    int date;
    struct node *next;
} task;

int input(int *n, int i);
void sinput(char *array, int n);
int sign_up(char *name);
int log_in(char *name);
int making_boards_and_lists();
int view(int *s, char buffer[100]);
void free2DArray(char **arr, int rows);
int Delete();
int add_task(task *head);
int tprint();
int delete_task(char buffer[1024]);
int EDIT();
int settings(char *name);
int reminder();
int remove_directory(const char *path);

int main()
{
    // Initialization of head node for the task linked list
    task *head;
    head = malloc(sizeof(task));
    char x;
    char buffer[100];
    char dum[1024];
    char *buffer2;
    buffer2 = malloc(sizeof(char));
    char *buffer3;
    buffer3 = malloc(sizeof(char));

    // Main program loop
    while (1)
    {
        // signup/signin page
        char *name;
        name = malloc(sizeof(char) * 256);
        printf("-----------------------------------------------------------------------------------------\n");
        printf("are you already have an account?\nif yes press 1, and if no\npress 2 and make an account :)\n\n1. log_in\n2. sign_up ");
        printf("\n-----------------------------------------------------------------------------------------\n");
        while (1)
        {
            x = getch();
            // signup user
            if (x == 50)
            {
                while (1)
                {
                    // check if user exist or not
                    if (sign_up(name) == 0)
                    {
                        break;
                    }
                    system("cls");
                    printf("This acount exist! please try another name...\n");
                }
                break;
            }
            // login user
            if (x == 49)
            {
                while (1)
                {
                    if (log_in(name) == 0)
                    {
                        break;
                    }
                    system("cls");
                    printf("there is no such an account");
                }
                break;
            }
            printf("\nyou entered wrong key, please try again ~>");
        }

        // open board ui
        while (1)
        {
            printf("1. view Boards\n2. Create New Boards\n3. Delete Board\n4. Settings\n5.Exit\n\n");
            reminder();
            fflush(stdin);
            int c = getch();
            int s;
            system("cls");
            switch (c)
            {

            // print all boardes
            case '1':
            {
                printf("Available Boards: \n");
                view(&s, buffer);
                system("cls");
                // check if board exist or not
                if (s == 1)
                {
                    system("cls");
                    printf("THERE IS NO BOARD!");
                    Sleep(1000);
                    system("cls");
                    s = 0;
                    break;
                }
                int z;
                strcpy(buffer3, buffer);
                while (1)
                {
                    // open list ui
                    printf("Board: <%s> \n", buffer3);
                    printf("1. View List\n2. Create New list\n3. Delete List\n4. Go Back\n");
                    int x = getch();
                    system("cls");
                    switch (x)
                    {
                    // view list
                    case '1':
                    {
                        printf(" Lists in <%s> Board:", buffer3);
                        view(&s, buffer);
                        system("cls");
                        if (s == 1)
                        {
                            system("cls");
                            printf("THERE IS NO LIST!");
                            Sleep(1000);
                            system("cls");
                            s = 0;
                            continue;
                        }
                        strcpy(buffer2, buffer);
                        while (1)
                        {
                            // open task ui
                            printf("List: <%s>\n\nTASKS:", buffer);
                            tprint();
                            printf("\n\nOptions:\n1. Add Task\n2. Edit Task\n3. Delete Task\n4. Move Task To Another List\n5. GO BACK");
                            int p = 0;
                            int t = getch();
                            system("cls");
                            switch (t)
                            {
                            // in this place you can add a task
                            case '1':
                            {
                                fflush(stdin);
                                add_task(head);
                            }
                                continue;
                            // in this place you can edit task
                            case '2':
                            {
                                fflush(stdout);
                                EDIT();
                                continue;
                            }
                            // in this place you can delete task
                            case '3':
                            {
                                printf("Delete Task:\n\nWhich Task Do You Want To Delete?\n");
                                delete_task(dum);
                                continue;
                            }
                            // in this place you can mvoe task to another list that you targeted
                            case '4':
                            {
                                printf("Move Task To Another List:\n\nWhich Task Do You Want To Move?\n");
                                delete_task(dum);
                                chdir("..");
                                printf("Which List Would You Like To Move The Task To?\n");
                                view(&s, buffer);
                                system("cls");
                                FILE *new = fopen("task.csv", "a");
                                fprintf(new, "%s", dum);
                                fclose(new);
                                continue;
                            }
                            // back to the list ui
                            case '5':
                            {
                                fflush(stdin);
                                fflush(stdin);
                                p++;
                                chdir("..");
                            }
                            // if user enter an invalid number
                            default:
                                break;
                            }
                            if (p == 1)
                            {
                                break;
                            }
                        }
                        continue;
                    }
                    // in this place you can add a new list
                    case '2':
                    {
                        fflush(stdin);
                        system("cls");
                        printf("Add New List to <%s>:\n", buffer);
                        printf("What's the name of the new List? ");
                        making_boards_and_lists();
                        continue;
                    }
                    // in this place you can delete a list that you want
                    case '3':
                    {
                        fflush(stdin);
                        printf("Delete list from <%s>:\n", buffer);
                        printf("Which List Do you want to Delete?\n");
                        Delete();
                        continue;
                    }
                    // back to the board ui
                    case '4':
                    {
                        z = 1;
                        system("cls");
                        chdir("..");
                        break;
                        ;
                    }
                    // if user enter an invalid number
                    default:
                        continue;
                    }
                    if (z)
                    {
                        break;
                    }
                    system("cls");
                }
                z = 0;
                break;
            }
            // in this place you can create a new board
            case '2':
            {
                fflush(stdin);
                printf("whats the name of the new Board?");
                making_boards_and_lists();
                break;
            }
            // in this place you can destroyed a board that you command
            case '3':
            {
                fflush(stdin);
                Delete();
                break;
            }
            // in this place you can customize your ui and changing your password to the new password
            case '4':
            {
                settings(name);
                break;
            }
            // in this place you exit the app
            case '5':
            {
                exit(-1);
            }
            // if user enter an invalid number
            default:
                break;
            }
            system("cls");
        }
        // free all alocated memeory for prevent to the memory leak
        free(name);
        free(buffer2);
        free(buffer3);
    }
    return 0;
}

// signup system (if user want to create a new account)
int sign_up(char *name)
{
    char username[100];
    char passkey[100];
    // get the username form user
    printf("please enter your username:\n");
    sinput(username, 100);
    // making directory with username
    if (mkdir(username) == 0)
    {
        printf("hello <%s> now make sure you have a strong password :)\n", username);
    }
    else
    {
        return -1;
    }
    if (chdir(username) != 0)
    {
        perror("Error changing directory");
        return 1;
    }

    // get password from user
    printf("Please enter your password :\n");
    sinput(passkey, 100);
    FILE *password = fopen("password.csv", "wb");

    // make a file (password.csv) that contain the user's password in it
    if (password == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    fprintf(password, "%s", passkey);
    fclose(password);
    strcpy(name, username);
    system("cls");
    return 0;
}

// login system (if user want to open his own account)
int log_in(char *name)
{

    char username[100];
    char passkey[100];
    char filepath[200];
    char *key = NULL;
    // getting access to the password file and usernames
    FILE *password;
    while (1)
    {
        printf("please enter your username:\n");
        sinput(username, 100);
        if (chdir(username) != 0)
        {
            printf("there is no such an account");
            return 1;
        }
        else
        {
            printf("hello <%s>, Im so happy to see you :)\n", username);
            break;
        }
    }
    snprintf(filepath, sizeof(filepath), "password.csv");

    // put password in variable for checking the verification of password
    password = fopen(filepath, "r");
    if (password == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    fseek(password, 0, SEEK_END);
    long length = ftell(password);
    fseek(password, 0, SEEK_SET);

    key = (char *)malloc(length + 1); // +1 for null-termination
    if (key == NULL)
    {
        perror("Memory allocation error");
        fclose(password);
        return 1;
    }

    fread(key, 1, length, password);
    key[length] = '\0'; // Ensure null-termination
    while (1)
    {
        // get password from user
        printf("%s Please enter your password:\n", username);
        fgets(passkey, 100, stdin);
        int num = strlen(passkey);
        if (passkey[num - 1] == '\n')
        {
            passkey[num - 1] = '\0';
        }
        system("cls");

        int u = strcmp(key, passkey);
        // if password correct
        if (u == 0)
        {
            printf("Welcome, %s!\n", username);
            break;
        }
        // if password incorrect
        else
        {
            printf("Incorrect password.\n");
        }
    }
    strcpy(name, username);
    free(key);
    fclose(password);
    return 0;
}

// create the new board and list system
int making_boards_and_lists()
{
    char name[100];
    char filepath[200];
    sinput(name, 100);
    // making directory with the name of board or list that user entered
    if (mkdir(name) == 0)
    {
        printf("%s sucsessfuly added!", name);
        Sleep(1000);
        system("cls");
    }
    // if that board or list is exist
    else
    {
        printf("already excist.\n");
        Sleep(1000);
        return 0;
    }
    snprintf(filepath, sizeof(filepath), "name.csv");
    FILE *table = fopen(filepath, "ab");
    if (table == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    fprintf(table, "%s,", name);
    fclose(table);
}

// show the content of the board, list and tasks to the user
int view(int *s, char buffer[100])
{
    char line[256];
    int length = 0;
    int i = 0;

    // Get the current working directory
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);

    // Build the full path to the file
    char filepath[FILENAME_MAX];
    snprintf(filepath, sizeof(filepath), "%s\\name.csv", currentDir);

    // access to the board file that user choosen
    FILE *name = fopen(filepath, "rb");
    if (name == NULL)
    {
        printf("THERE IS NOTHING!");
        *s = 1;
        return 0;
    }

    // split the file content with ',' using strtok()
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            i++;
            printf("\n%d. %s  ", i, s);
            s = strtok(NULL, ",");
            length++;
        }
    }
    printf("\n~> ");
    fclose(name);

    // allocating 2D array
    char **list = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        list[i] = malloc(sizeof(char) * 100);
    }
    i = 0;

    // saving that names to an 2D array
    name = fopen(filepath, "rb");
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            list[i] = s;
            s = strtok(NULL, ",");
            i++;
        }
    }
    int n;
    input(&n, i);
    // if board or list doesn't exist
    if (chdir(list[n - 1]) != 0)
    {
        printf("there is nothing");
    }

    // if board or list does exist
    else
    {
        printf("<%s> is now open\n", list[n - 1]);
        strcpy(buffer, list[n - 1]);
    }
    fclose(name);
    free2DArray(list, length);
    return 1;
}

// for making memeory free from 2Darray (for preventing the memeory leak)
void free2DArray(char **arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

// for delete the boards or lists
int Delete()
{
    char line[256];
    int length = 0;
    int i = 0;

    // Get the current working directory
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);

    // Build the full path to the file
    char filepath[FILENAME_MAX];
    snprintf(filepath, sizeof(filepath), "%s\\name.csv", currentDir);

    // opening file 
    FILE *name = fopen(filepath, "rb");

    // check if there is anything to delete or not
    if (name == NULL)
    {
        printf("There is Nothing to Delete!");
        Sleep(3000);
        system("cls");
        return 1;
    }

    // using for view the board or list that the user want to delete
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            i++;
            printf("\n%d. %s  ", i, s);
            s = strtok(NULL, ",");
            length++;
        }
    }
    printf("\n~> ");

    // allocating 2Darray
    char **list = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        list[i] = malloc(sizeof(char) * 100);
    }
    i = 0;
    fseek(name, 0, SEEK_SET);
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            list[i] = s;
            s = strtok(NULL, ",");
            i++;
        }
    }
    fclose(name);
    int n;
    input(&n, i);
    // removing board or list that user selected (removing directory)
    if (remove_directory(list[n - 1]) == 0)
    {
        printf("\n%s is sucsessfully Deleted!", list[n - 1]);
        Sleep(3000);
        system("cls");
    }
    // delete the board name from name.csv file
    name = fopen(filepath, "w");
    fclose(name);
    name = fopen(filepath, "a");
    for (i = 0; i < length; i++)
    {
        if (i != (n - 1))
        {
            fprintf(name, "%s,", list[i]);
        }
    }
    fclose(name);
    length--;
    // check if all names deleted from the file, so delete the name.csv file 
    if (length == 0)
    {
        DeleteFile(filepath);
    }
    free2DArray(list, length);
}

// adding task system
int add_task(task *head)
{
    // make an structor for the data of task
    task *current;
    current = head;
    current->next = malloc(sizeof(task));
    current = current->next;
    current->name = malloc(sizeof(char) * 100);
    if (current->name == NULL)
    {
        return 0;
    }

    // get the task data form user for creating a task (name, preority, deadline) 
    printf("Please Enter Your Task name: ");
    sinput(current->name, 100);
    current->priority = malloc(sizeof(char) * 100);
    system("cls");
    printf("Please Enter Your Task Priority (Low\\Medium\\High): ");
    sinput(current->priority, 100);
    system("cls");
    printf("Please Enter Your Task Deadline (YYYY-MM-DD): ");
    scanf("%4d-%2d-%2d", &current->year, &current->month, &current->day);
    system("cls");
    FILE *task = fopen("task.csv", "a");
    if (task == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    // put the data in the task.csv file
    fprintf(task, "%s,%s,%d,%d,%d,\n", current->name, current->priority, current->year, current->month, current->day);
    fclose(task);
    free(current->name);
    free(current->priority);
    free(current);
    return 0;
}

// removing directory system
int remove_directory(const char *path)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    // Create a search path for all files and subdirectories
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    // Start finding the first file/directory
    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        // No files or directories found
        return RemoveDirectory(path) != 0 ? 0 : -1;
    }

    do
    {
        // Skip "." and ".." directories
        if (strcmp(findFileData.cFileName, ".") != 0 &&
            strcmp(findFileData.cFileName, "..") != 0)
        {
            // Create the full path to the file/directory
            char filePath[MAX_PATH];
            snprintf(filePath, sizeof(filePath), "%s\\%s", path, findFileData.cFileName);

            // Recursively remove subdirectories and files
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (remove_directory(filePath) != 0)
                {
                    FindClose(hFind);
                    return -1;
                }
            }
            else
            {
                if (remove(filePath) != 0)
                {
                    FindClose(hFind);
                    return -1;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    // Remove the empty directory
    return RemoveDirectory(path) != 0 ? 0 : -1;
}

// printing task system
int tprint()
{
    int nl = 1;
    char *num;
    num = malloc(sizeof(char) * 4);
    task *buffer;
    buffer = malloc(sizeof(task));
    char *line;
    line = malloc(sizeof(char) * 1024);

    // open the task file
    FILE *task = fopen("task.csv", "r");
    // if there was no task to show
    if (task == NULL)
    {
        printf("\n\n\t\t<<There Is No Task Yet>>");
        return 1;
    }
    // get data from task.csv file for showing that to user
    while (fgets(line, 1024, task) != NULL)
    {
        buffer->name = strtok(line, ",");
        buffer->priority = strtok(NULL, ",");
        num = strtok(NULL, ",");
        buffer->year = atoi(num);
        num = strtok(NULL, ",");
        buffer->month = atoi(num);
        num = strtok(NULL, ",");
        buffer->day = atoi(num);
        printf("\n%d. Task: %s, Priority: %s, Deadline: %d-%d-%d", nl, buffer->name, buffer->priority, buffer->year, buffer->month, buffer->day);
        nl++;
    }
    fclose(task);
    // free all alocated memeory for prevent to the memory leak
    free(num);
    free(buffer);
    free(line);
    return 0;
}

// task delete stystem
int delete_task(char buffer[1024])
{
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);
    char filepath[FILENAME_MAX];
    // handle the file path
    snprintf(filepath, sizeof(filepath), "%s\\task.csv", currentDir);
    int i = 1;

    // open task file
    FILE *remove = fopen("task.csv", "r");
    char *taskname;
    char *line;
    line = malloc(sizeof(char) * 1024);

    // get task data from file
    while (fgets(line, 1024, remove) != NULL)
    {
        taskname = malloc(sizeof(char) * 256);
        strcpy(taskname, strtok(line, ","));
        printf("%d. %s\n", i, taskname);
        i++;
        free(taskname);
    }
    i--;
    free(line);
    line = malloc(sizeof(char) * 1024);
    printf("~>");
    fseek(remove, 0, SEEK_SET);
    char **list = malloc(sizeof(char *) * i);
    for (int j = 0; j < i; j++)
    {
        list[j] = malloc(sizeof(char) * 1024);
    }
    int t = 0;
    while (fgets(line, 1024, remove) != NULL)
    {
        list[t] = strdup(line);
        t++;
    }
    free(line);
    int n;
    input(&n, i);
    fclose(remove);
    remove = fopen("task.csv", "w");
    fclose(remove);
    remove = fopen("task.csv", "a");
    // delete the task that user want and delete that task from the task.csv file
    for (int j = 0; j < i; j++)
    {
        if (j != (n - 1))
        {
            fprintf(remove, "%s", list[j]);
        }
    }
    strcpy(buffer, list[n - 1]);
    fclose(remove);
    // free the 2D array 
    free2DArray(list, i);
    i--;
    if (i == 0)
    {
        DeleteFile(filepath);
    }
    system("cls");
}

// get a number from user in an certain range of options (get int)
int input(int *n, int i)
{
    while (1)
    {
        if (scanf("%d", n) == 1 && *n >= 1 && *n <= i)
        {
            break;
        }
        else
        {
            printf("\nyour input is unfortunately wrong please enter again (:");
            printf("\n~> ");
            while (getchar() != '\n')
                ;
        }
    }
}

// get a string from user and null terminate the string (get string)
void sinput(char *array, int n)
{
    fgets(array, n, stdin);
    int num = strlen(array);
    if (array[num - 1] == '\n')
    {
        array[num - 1] = '\0';
    }
}

// edit task that user want to change
int EDIT()
{
    int i = 1;
    // ask the user what task do you want to edit?
    printf("Edit Task:\n\nWhich Task Do You Want To Edit?\n");
    FILE *edit = fopen("task.csv", "r");
    char *taskname;
    char *line;
    line = malloc(sizeof(char) * 1024);
    // reading the task data taht user selected
    while (fgets(line, 1024, edit) != NULL)
    {
        taskname = malloc(sizeof(char) * 256);
        strcpy(taskname, strtok(line, ","));
        printf("%d. %s\n", i, taskname);
        i++;
        free(taskname);
    }
    i--;
    free(line);
    line = malloc(sizeof(char) * 1024);
    printf("~>");
    fseek(edit, 0, SEEK_SET);
    // allocating the 2D array
    char **list = malloc(sizeof(char *) * i);
    for (int j = 0; j < i; j++)
    {
        list[j] = malloc(sizeof(char) * 1024);
    }
    int t = 0;
    // saving the tasks in a 2D array
    while (fgets(line, 1024, edit) != NULL)
    {
        list[t] = strdup(line);
        t++;
    }

    // free alocated memeory for prevent to the memory leak
    free(line);
    int n;
    input(&n, i);

    // making a node in task structor
    task *current;
    current = malloc(sizeof(task));
    current->next = malloc(sizeof(task));
    current = current->next;
    current->name = malloc(sizeof(char) * 100);
    if (current->name == NULL)
    {
        return 0;
    }
    fflush(stdin);
    // get edited data from user
    printf("Edit  Task Name: ");
    sinput(current->name, 100);
    current->priority = malloc(sizeof(char) * 100);
    system("cls");
    printf("Edit  Priority: ");
    sinput(current->priority, 100);
    system("cls");
    printf("Edit  Deadline (YYYY-MM-DD): ");
    scanf("%4d-%2d-%2d", &current->year, &current->month, &current->day);

    // close the used files 
    fclose(edit);
    edit = fopen("task.csv", "w");
    fclose(edit);
    edit = fopen("task.csv", "a");
    // write all task and edited task
    for (int j = 0; j < i; j++)
    {
        if (j != (n - 1))
        {
            fprintf(edit, "%s", list[j]);
        }
        else
        {
            fprintf(edit, "%s,%s,%d,%d,%d,\n", current->name, current->priority, current->year, current->month, current->day);
        }
    }
    fclose(edit);
    free2DArray(list, i);
    system("cls");
}

// setting system (color theme, and pasword changing)
int settings(char *name)
{
    char *newpass;
    newpass = malloc(sizeof(char) * 256);
    int n;
    system("cls");
    printf("<%s>\n1. change password \n2. Theme\n~>", name);
    input(&n, 3);
    switch (n)
    {
        // changing the user password
    case 1:
    {
        system("cls");
        printf("Please Enter your new password:\n");
        fflush(stdin);
        sinput(newpass, 256);
        FILE *password = fopen("password.csv", "w");
        fprintf(password, "%s", newpass);
        fclose(password);
        break;
    }
    // changing the color ui theme
    case 2:
    {
        system("cls");
        int num;
        printf("What Theme do you Like?\n1. dark\n2. light\n3. blue\n4. green\n~> ");
        input(&num, 4);
        switch (num)
        {
            // apply dark theme
        case 1:
        {
            system("color 07");
        }
        break;

        // apply light theme
        case 2:
        {
            system("color 70");
        }
        break;
        // apply blue theme
        case 3:
        {
            system("color 17");
        }
        break;
        // apply green theme
        case 4:
        {
            system("color 27");
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
    free(newpass);
}

// the reminder system
int reminder()
{
    // seting the current time
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1; // tm_mon is 0-indexed
    int length = 1;

    // access to the boards name file
    FILE *boards_f = fopen("name.csv", "r");

    if (boards_f != NULL) // if there is a boards file
    {
        char boards[1024];
        fgets(boards, 1024, boards_f);
        // read all boards name
        char *board = malloc(sizeof(char) * 100);
        board = strtok(boards, ",");
        printf("Upcoming Tasks:\n");
        while (board != NULL)
        {
            board = strtok(NULL, ",");
            length++;
        }
        char **table = malloc(sizeof(int) * length);
        for (int i = 0; i < length; i++)
        {
            table[i] = malloc(sizeof(char) * 100);
        }
        fseek(boards_f, 0, SEEK_SET);
        fgets(boards, 1024, boards_f);
        board = strtok(boards, ",");
        int i = 0;
        while (board != NULL)
        {
            table[i] = board;
            board = strtok(NULL, ",");
            i++;
        }
        char path[1024];
        int j = 0;
        for (i = 0; i < length; i++)
        {
            // Copy the first string into the variable
            strcpy(path, table[i]);
            strcat(path, "/name.csv"); // path of (list name file)

            // access to the lists name file
            FILE *lists_f = fopen(path, "r");
            strcpy(path, table[i]); // reset path to board

            if (lists_f != NULL)
            {
                char lists[1024];
                fgets(lists, sizeof(lists), lists_f);

                // read all lists name
                char *list = strtok(lists, ",");
                char line[1024];
                while (list != NULL)
                {

                    // setting path
                    strcpy(path, table[i]);
                    strcat(path, "/");
                    strcat(path, list);
                    strcat(path, "/task.csv");
                    FILE *task = fopen(path, "r");

                    // Move to the next list
                    list = strtok(NULL, ",");

                    while (fgets(line, sizeof(line), task) != NULL)
                    {

                        // geting task data (name, priority, deadline)
                        char *name = strtok(line, ",");
                        char *priority = strtok(NULL, ",");
                        int year = atoi(strtok(NULL, ","));
                        int month = atoi(strtok(NULL, ","));
                        int day = atoi(strtok(NULL, ","));

                        // Check if the task is due within the next 3 days
                        if (year == current_time->tm_year + 1900 && // tm_year is years since 1900
                                (month == current_month && day - current_day <= 3) ||
                            (month == current_month + 1 && day + (30 - current_day) <= 3))
                        {
                            j++;
                            printf("%d. Task: %s, Priority: %s, Deadline: %d-%d-%d\n", j,
                                   name, priority, year, month, day);
                        }
                    }
                    fclose(task);
                }
            }
        }
        fclose(boards_f);
        free2DArray(table, length);
    }
}
