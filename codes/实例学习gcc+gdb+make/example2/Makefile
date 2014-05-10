# main:main.c add.c
# 	gcc -D_DEBUG main.c add.c sub.c -o main
# 
# main:main.o add.o sub.o
# 	gcc main.o add.o sub.o -o main
# 
# 
# main.o:main.c
# 	gcc -c -D_DEBUG main.c -o main.o
# add.o:add.c
# 	gcc -c add.c -o add.o
# sub.o:sub.c
# 	gcc -c sub.c -o sub.o

# CC=gcc
# OBJS=main.o add.o sub.o
# CFLAGS=-D_DEBUG
# 
# main:$(OBJS)
# 	$(CC) $(CFLAGS) $^ -o $@
# 
# main.o:main.c
# 	$(CC) $(CFLAGS) -c $^ -o $@
# add.o:add.c
# 	$(CC) $(CFLAGS) -c $^ -o $@
# sub.o:sub.c
# 	$(CC) $(CFLAGS) -c $^ -o $@

# CC=gcc
# OBJS=main.o add.o sub.o
# CFLAGS=-D_DEBUG
# 
# main:$(OBJS)
# 	$(CC) $(CFLAGS) $^ -o $@
# 
# %.o:%.c
# 	$(CC) $(CFLAGS) -c $^ -o $@

CC=gcc
OBJS=main.o add.o sub.o
CFLAGS=-D_DEBUG -g

main:$(OBJS)
	$(CC) $^ -o $@

# main.o:
# add.o:add.h
# sub.o:sub.h
%.o:add.h sub.h

.PHONY:clean
clean:
	-rm main *.o
