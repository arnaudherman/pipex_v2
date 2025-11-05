# Pipex - Reproduction du pipe shell

![C](https://img.shields.io/badge/language-C-blue.svg)
![42](https://img.shields.io/badge/school-42-000000.svg)

## 📚 À propos

**Pipex** reproduit le comportement des pipes UNIX en C. Ce projet permet de comprendre la communication entre processus, les redirections et l'exécution de commandes système.

Implémentation personnelle par **aherman** (@arnaudherman) - 42 Lausanne

## 🎯 Fonctionnement

Reproduit la commande shell :
```bash
< file1 cmd1 | cmd2 > file2
```

Avec le programme :
```bash
./pipex file1 cmd1 cmd2 file2
```

## 🏗️ Architecture du code

### Structure `t_info` centralisée

```c
typedef struct s_info
{
    int     _pipe[2];     // Le pipe pour la communication
    int     fd1;          // File descriptor input
    int     fd2;          // File descriptor output
    char    *cmd1;        // Chemin complet de la commande 1
    char    *cmd2;        // Chemin complet de la commande 2
    char    **split1;     // Arguments de cmd1 splittés
    char    **split2;     // Arguments de cmd2 splittés
    pid_t   p_id_c1;      // PID du processus enfant 1
    pid_t   p_id_c2;      // PID du processus enfant 2
}   t_info;
```

### Organisation des fichiers

```
src/
├── pipex.c           # Main + recherche PATH + orchestration
├── pipex_childs.c    # Gestion des processus enfants
├── pipex_split.c     # ft_split personnalisé
├── pipex_utils.c     # Fonctions utilitaires
include/
└── pipex.h           # Header principal
ft_printf/            # ft_printf intégré
```

## 🔧 Fonctions clés de l'implémentation

### 1. `ft_get_path()` - Recherche intelligente des commandes

```c
char *ft_get_path(char **envp, char *cmd)
```

**Ce qu'elle fait :**
- Trouve la ligne `PATH=` dans `envp` avec `ft_find_envp()`
- Split le PATH par `':'` pour obtenir tous les chemins
- Pour chaque chemin :
  - Construit `chemin + "/" + cmd`
  - Teste avec `access(X_OK | F_OK)`
  - Retourne le premier chemin valide
- Libère proprement toute la mémoire allouée

### 2. Validation stricte dans `main()`

```c
if (argc != 5 || argv[2][0] == '\0' || argv[3][0] == '\0')
```

**Vérifie :**
- Exactement 5 arguments (pas plus, pas moins)
- Les commandes ne sont **pas vides** (protection contre `""`)
- Messages d'erreur personnalisés selon le cas

### 3. `child_one()` - Premier processus

```c
void child_one(t_info *info, char **envp)
{
    close(info->_pipe[0]);                  // Ferme lecture du pipe
    dup2(info->fd1, STDIN_FILENO);          // Redirige stdin vers file1
    dup2(info->_pipe[1], STDOUT_FILENO);    // Redirige stdout vers pipe
    close(info->fd1);
    close(info->_pipe[1]);
    execve(info->cmd1, info->split1, envp); // Execute cmd1
}
```

### 4. `child_two()` - Second processus avec synchronisation

```c
void child_two(t_info *info, char **envp)
{
    dup2(info->fd2, STDOUT_FILENO);         // Redirige stdout vers file2
    dup2(info->_pipe[0], STDIN_FILENO);     // Redirige stdin depuis pipe
    close(info->_pipe[1]);
    close(info->fd2);
    waitpid(info->p_id_c1, &status, 0);     // ⚠️ Attend child_one
    execve(info->cmd2, info->split2, envp); // Execute cmd2
}
```

**Particularité :** `child_two()` attend explicitement que `child_one` termine avant d'exécuter sa commande.

## 💻 Compilation

```bash
make        # Compile le projet
make clean  # Nettoie les .o
make fclean # Nettoie tout
make re     # Recompile tout
```

## 🚀 Utilisation

### Format

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Exemples

```bash
# Équivalent : < input.txt grep hello | wc -l > output.txt
./pipex input.txt "grep hello" "wc -l" output.txt

# Équivalent : < file.txt cat | cat > out.txt
./pipex file.txt "cat" "cat" out.txt

# Avec options
./pipex input.txt "ls -l" "grep .c" output.txt
```

## 🔍 Gestion des erreurs

### Messages personnalisés

```c
if (argc != 5)
    ft_putendl_fd("Error: Invalid number of arguments", 2);
else
    ft_putendl_fd("Error: Command null", 2);
```

### Validation des commandes

```c
if (info->cmd1 == 0)
    ft_error(1);  // "Error: command does not exist"
```

### Erreurs système

```c
ft_error(-1);  // Utilise perror("Error")
```

## 📋 Fonctions utilitaires réécrites

Toutes les fonctions sont implémentées dans le projet (pas de libft externe) :

- `ft_split()` - Split personnalisé avec gestion mémoire
- `ft_strlen()` - Calcul de longueur
- `ft_strdup()` - Duplication de chaîne
- `ft_strjoin()` - Concaténation avec malloc
- `ft_strncmp()` - Comparaison de chaînes
- `ft_putendl_fd()` - Affichage avec retour ligne
- `ft_free_char()` - Libération de tableau de chaînes

## 🧪 Tests

### Tests basiques

```bash
# Test simple
echo "hello world" > input.txt
./pipex input.txt "cat" "cat" output.txt
cat output.txt  # Doit afficher "hello world"

# Test avec grep et wc
echo -e "hello\nworld\nhello" > input.txt
./pipex input.txt "grep hello" "wc -l" output.txt
cat output.txt  # Doit afficher "2"
```

### Comparaison avec le shell

```bash
# Avec le shell
< input.txt grep a | wc -l > expected.txt

# Avec pipex
./pipex input.txt "grep a" "wc -l" output.txt

# Comparer
diff expected.txt output.txt
```

### Tests d'erreurs

```bash
# Mauvais nombre d'arguments
./pipex file1 "cat"
# Sortie : "Error: Invalid number of arguments"

# Commande vide
./pipex input.txt "" "cat" output.txt
# Sortie : "Error: Command null"

# Commande inexistante
./pipex input.txt "invalidcmd" "cat" output.txt
# Sortie : "Error: command does not exist"

# Fichier inexistant
./pipex nofile "cat" "cat" output.txt
# Sortie : "Error: [message système]"
```

### Vérifier les fuites mémoire

```bash
valgrind --leak-check=full --show-leak-kinds=all \
  ./pipex input.txt "cat" "grep a" output.txt
```

## 🎯 Points techniques importants

### 1. Ouverture du fichier de sortie

```c
info.fd2 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
```
- **O_CREAT** : Crée le fichier s'il n'existe pas
- **O_TRUNC** : Vide le fichier s'il existe déjà
- **0000644** : Permissions rw-r--r--

### 2. Gestion du pipe

```c
if (pipe(info->_pipe) < 0)
    ft_error(-1);
```
- `info->_pipe[0]` : lecture
- `info->_pipe[1]` : écriture

### 3. Fork et processus

```c
info->p_id_c1 = fork();
if (info->p_id_c1 == 0)
    child_one(info, envp);  // Code du processus enfant
// Code du processus parent continue ici
```

### 4. Fermeture des descripteurs dans le parent

```c
close(info->_pipe[0]);
close(info->_pipe[1]);
waitpid(info->p_id_c1, &status, 0);
waitpid(info->p_id_c2, &status, 0);
```

## 📝 Norminette

Le code respecte la norme de 42 :
- ✅ Maximum 25 lignes par fonction
- ✅ Maximum 5 fonctions par fichier
- ✅ Pas de variables déclarées après les instructions
- ✅ Gestion propre de la mémoire

## 🔗 Dépendances

- **ft_printf** : Intégré dans le projet (dossier `ft_printf/`)

## 👨‍💻 Auteur

**Arnaud Herman** (@arnaudherman)  
École 42 Lausanne  
Projet réalisé en septembre 2023

---

*"Two processes, one pipe, infinite possibilities."* 🔧✨
