# Pipex - Communication entre processus avec des pipes

![C](https://img.shields.io/badge/language-C-blue.svg)
![42](https://img.shields.io/badge/school-42-000000.svg)

## 📚 À propos

**Pipex** est un projet système de l'école 42 qui reproduit le comportement des pipes du shell. Il permet de comprendre la communication entre processus, les redirections, et l'exécution de commandes.

Ce projet permet de maîtriser :
- Les pipes (`|`) en UNIX/Linux
- La gestion des processus (`fork`, `execve`)
- Les file descriptors et redirections
- La communication inter-processus

## 🎯 Objectif

Créer un programme qui reproduit le comportement suivant du shell :

```bash
< file1 cmd1 | cmd2 > file2
```

Avec votre programme :

```bash
./pipex file1 cmd1 cmd2 file2
```

## 🔧 Fonctionnement

Le programme doit :
1. Lire depuis `file1`
2. Exécuter `cmd1` avec `file1` en entrée
3. Passer la sortie de `cmd1` à `cmd2` via un pipe
4. Écrire le résultat de `cmd2` dans `file2`

### Exemple

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Équivalent à :

```bash
< infile grep hello | wc -l > outfile
```

## 📦 Structure du projet

```
pipex.c               # Programme principal
pipex.h               # Header
parsing.c             # Parsing des arguments et commandes
execution.c           # Exécution des commandes
pipes.c               # Gestion des pipes
utils.c               # Fonctions utilitaires
error.c               # Gestion des erreurs
Makefile              # Compilation
```

## 💻 Compilation

```bash
# Compiler le programme
make

# Nettoyer les fichiers objets
make clean

# Nettoyer tous les fichiers générés
make fclean

# Recompiler entièrement
make re
```

## 🚀 Utilisation

### Format de base

```bash
./pipex file1 cmd1 cmd2 file2
```

### Exemples pratiques

```bash
# Exemple 1 : Chercher et compter
./pipex input.txt "grep 42" "wc -l" output.txt

# Exemple 2 : Lister et trier
./pipex input.txt "cat" "sort" output.txt

# Exemple 3 : Avec options
./pipex input.txt "grep -i hello" "wc -w" output.txt
```

### Comparaison avec le shell

```bash
# Avec pipex
./pipex infile "ls -l" "grep txt" outfile

# Équivalent shell
< infile ls -l | grep txt > outfile
```

## 🎯 Fonctions système utilisées

| Fonction | Description |
|----------|-------------|
| `fork()` | Crée un nouveau processus |
| `pipe()` | Crée un pipe pour la communication |
| `dup2()` | Duplique un file descriptor |
| `execve()` | Remplace le processus par une commande |
| `access()` | Vérifie les permissions d'un fichier |
| `wait()` / `waitpid()` | Attend la fin d'un processus |
| `open()` | Ouvre un fichier |
| `close()` | Ferme un file descriptor |
| `read()` / `write()` | Lecture/écriture |
| `unlink()` | Supprime un fichier |

## 🧠 Concepts clés

### 1. Les Pipes

Un pipe permet de connecter la sortie d'un processus à l'entrée d'un autre :

```c
int pipefd[2];
pipe(pipefd);  // pipefd[0] = lecture, pipefd[1] = écriture
```

### 2. Fork

`fork()` crée un processus enfant :

```c
pid_t pid = fork();
if (pid == 0)
    // Code du processus enfant
else
    // Code du processus parent
```

### 3. Dup2

`dup2()` redirige les entrées/sorties :

```c
dup2(file_fd, STDIN_FILENO);   // Redirige stdin
dup2(pipe_fd, STDOUT_FILENO);  // Redirige stdout
```

### 4. Execve

`execve()` remplace le processus actuel par une commande :

```c
char *argv[] = {"grep", "hello", NULL};
execve("/usr/bin/grep", argv, envp);
```

## 📖 Gestion des erreurs

Le programme doit gérer :
- Fichiers inexistants ou sans permissions
- Commandes invalides
- Erreurs d'exécution
- Problèmes de mémoire
- Échec des appels système

```bash
# Erreurs possibles
./pipex nofile "cat" "grep a" outfile    # Fichier inexistant
./pipex infile "invalid_cmd" "cat" out   # Commande invalide
./pipex infile "ls" "wc" /root/out       # Permission refusée
```

## 🔄 Bonus

### Multiple pipes

Gérer plusieurs commandes en chaîne :

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Équivalent à :

```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

### Here_doc

Implémenter le comportement du `<<` :

```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

Équivalent à :

```bash
cmd1 << LIMITER | cmd2 >> file
```

Exemple :

```bash
./pipex here_doc EOF "grep hello" "wc -l" outfile
```

## 🧪 Tests

### Tests basiques

```bash
# Test 1 : Commandes simples
./pipex input.txt "cat" "cat" output.txt
diff input.txt output.txt

# Test 2 : Avec grep et wc
./pipex input.txt "grep a" "wc -l" output.txt

# Test 3 : Comparaison avec shell
< input.txt grep a | wc -l > expected.txt
./pipex input.txt "grep a" "wc -l" output.txt
diff expected.txt output.txt
```

### Tests d'erreurs

```bash
# Fichier inexistant
./pipex nofile "cat" "cat" out

# Commande invalide
./pipex input.txt "invalidcmd" "cat" out

# Permissions
./pipex /etc/shadow "cat" "cat" out
```

### Testeurs recommandés

- [pipex_tester](https://github.com/vfurmane/pipex-tester)
- Tests manuels avec comparaison shell

## 📚 Ressources

- [Sujet officiel (PDF)](https://raw.githubusercontent.com/aposipov/42cursus/main/subjects/2_pipex%282%29.pdf)
- [Guide complet Pipex](https://dev.to/herbievine/42-a-comprehensive-guide-to-pipex-5165)
- [Rapport détaillé](https://unam3dd.github.io/2024/05/16/pipex/)
- [Sujet (FR)](https://github.com/9x14S/42-Cursus-Subjects/blob/main/Cursus/pipex/fr.subject.pdf)
- [Sujet (EN)](https://github.com/Ian-Orwel/42-Cursus-Subjects)

## 💡 Conseils

1. **Commencez par la partie obligatoire** : Ne faites le bonus qu'après
2. **Testez avec le vrai shell** : Comparez toujours vos résultats
3. **Gérez les erreurs** : Testez tous les cas limites
4. **Fermez les file descriptors** : Évitez les fuites
5. **Utilisez valgrind** : Vérifiez les fuites mémoire
6. **Libérez PATH** : Attention aux variables d'environnement

### Commandes utiles pour déboguer

```bash
# Tracer les appels système
strace ./pipex infile "cat" "cat" outfile

# Vérifier les fuites mémoire
valgrind --leak-check=full ./pipex infile "cat" "cat" outfile

# Vérifier les file descriptors
lsof -p <PID>
```

## 🔍 Schéma du processus

```
┌─────────────┐
│   Parent    │
│   Process   │
└──────┬──────┘
       │ fork()
       ├──────────────────────┐
       │                      │
┌──────▼──────┐        ┌──────▼──────┐
│   Child 1   │  pipe  │   Child 2   │
│    cmd1     │───────>│    cmd2     │
└─────────────┘        └─────────────┘
    ▲                        │
    │ file1                  │ file2
```

## 👨‍💻 Auteur

Projet réalisé dans le cadre du cursus de l'école 42.

## 📝 Note

Pipex est un projet fondamental pour comprendre le fonctionnement des shells UNIX. Les concepts appris ici seront essentiels pour les projets suivants comme Minishell !

---

*"Everything is a file descriptor."* 🔧✨
