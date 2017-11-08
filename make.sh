NOME_EXECUTAVEL="main"

# Se o arquivo existir remove
if [ -f main ]; then
    rm $NOME_EXECUTAVEL
fi

# Compila o programa
gcc -o $NOME_EXECUTAVEL main.c lib/*.c
