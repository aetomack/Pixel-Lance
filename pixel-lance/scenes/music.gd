extends AudioStreamPlayer2D

# Called when the node enters the scene tree for the first time.
func _ready():
	# Set the song to loop
	stream.set_loop(true)
	
	# Play the song (if it isn't already playing)
	play()
