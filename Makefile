NAME = minirt
SRCS = minirt.c get_next_line.c get_next_line_utils.c ver_cal.c
OBJS = minirt.o get_next_line.o get_next_line_utils.o ver_cal.o

MLX = -L/users/thomamin/prj/minirt/lib/mlx -lmlx 
OPENGL = -framework OpenGL -framework AppKit


all : $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	cc $(MLX) $(OPENGL) $(OBJS) -o $(NAME)

bonus : $(OBJS)
	cc $(MLX) $(OPENGL) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)
.PHONY : clean

fclean : clean
	rm -rf $(NAME)
.PHONY : fclean

re : fclean
	make all
.PHONY : re
