extends MenuButton

# This will pause the game when the MenuButton is clicked
func _ready():
	var popup = get_popup()
	popup.clear()

	# Add items to the menu
	popup.add_item("Resume", 0)
	popup.add_separator()
	popup.add_item("Restart", 1)
	

	# Connect the signal to the callback function
	popup.connect("id_pressed", Callable(self, "_on_menu_selected"))
	
	# Set text to an empty string (if you just want an icon)
	set_text("") 

# This function will be called when a menu item is selected
func _on_menu_selected(id):
	match id:
		0:
			# Resume the game when "Resume" is selected
			print("Resume")
			get_tree().paused = false  # Unpause the game
		1:
			# Restart the game when "Restart" is selected
			print("Restart")
			get_tree().paused = false
			restart_game()
# Function to restart the game
func restart_game():
	# You can reload the current scene to restart the game
	get_tree().reload_current_scene()

# This function will be called when the MenuButton is pressed
func _pressed():
	# Pause the game when the menu is opened
	get_tree().paused = true
