NAME 		=	miniRT

CC 			=	cc
CFLAGS		=	-Werror -Wall -Wextra
RM			=	rm -f

SRC_DIR		=	./srcs/
INC_DIR		=	./includes
MLX_DIR		=	./mlx
LIBFT_DIR	=	./libft

SRC 		=	main.c \
				parser/parse_shape.c \
				parser/parse_points.c \
				parser/check_valid.c \
				parser/check_info.c \
				parser/parser_utils.c \
				parser/parser_main.c \
				get_next_line/get_next_line.c \
				ray/ray.c \
				ray/raytracer.c \
				ray/hit_object.c \
				ray/hit_sphere.c \
				ray/hit_cylinder.c \
				ray/hit_plane.c \
				ray/phong_lighting.c \
				scene/scene.c \
				scene/camera.c \
				objects/objects.c \
				objects/objects_utils.c \
				utils/error.c \
				utils/point_utils.c \
				utils/vector_utils.c \
				utils/vector_utils_2.c \
				utils/vector_utils_3.c \
				utils/mlx_utils.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC))

OBJS		=	$(SRCS:.c=.o)

MLX			=	libmlx.a

all: $(MLX) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<

$(MLX):
	@make all -C $(MLX_DIR)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(LIBFT_DIR)/libftprintf.a -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $@ $^
	

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make clean -C mlx

fclean: clean
	@$(RM) $(NAME)	
	@make -C $(LIBFT_DIR) fclean
	@make clean -C mlx
	
re: fclean all

.PHONY: all clean fclean re