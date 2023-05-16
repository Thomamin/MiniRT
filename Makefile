NAME = minirt
SRCS = minirt.c get_next_line.c get_next_line_utils.c ver_cal.c \
	   mrt_cam_init.c mrt_hit_obj.c mrt_input.c mrt_ratio.c \
	   mrt_ray_color.c mrt_set.c mrt_shadow.c mrt_utils.c
OBJS = $(SRCS:.c=.o)
MLX = -L/users/thomamin/prj/minirt/lib/mlx -lmlx 
OPENGL = -framework OpenGL -framework AppKit

all : $(NAME)

%.o: %.c
	$(CC) -g -c $< -o $@

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
