extends CanvasLayer


# Called when the node enters the scene tree for the first time.
func _ready():
	var custom_cursor = load("res://assets/UI/Pointers/01.png")
	Input.set_custom_mouse_cursor(custom_cursor, Input.CURSOR_ARROW)
