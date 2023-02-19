CC= gcc
CFLAGS= -w
DEPS = avlcharlib.h

dicionario: dicionario.c $(DEPS)
	$(CC) $(CFLAGS) -o dicionario dicionario.c 
test: dicionario input
	@./dicionario <input >output
	@echo "Resultado do teste armazenado no arquivo output"
clean: 
	@if [ -f ./dicionario ]; then rm dicionario; fi
	@if [ -f ./output ]; then rm output; fi
