# Nome do executável
EXEC = programa

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte e objetos
SRCS = main.c ingrediente.c pizza.c
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(EXEC)

# Linkagem final
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regras para compilar cada arquivo .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos temporários
clean:
	rm -f $(OBJS) $(EXEC)

# Executar o programa
run: $(EXEC)
	./$(EXEC)