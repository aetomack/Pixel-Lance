extends Node2D
@onready var game_root: Node2D = $"."

var enemy := preload("res://scenes/enemy.tscn")
@onready var path_follow_2d: PathFollow2D = $Player/Path2D/PathFollow2D
var wave = 0
var enemy_count = 0
var enemies_this_wave
var enemies_spawned_this_wave = 0
var num_waves = 2

func _ready():
	start_game()

# Spawn enemies for this wave
func _on_spawn_timer_timeout() -> void:
	if(enemies_spawned_this_wave < enemies_this_wave):
		var rng = RandomNumberGenerator.new()
		
		rng.randomize
		path_follow_2d.progress = rng.randi_range(0,3664)
		var instance = enemy.instantiate()
		
		instance.position = $Player/Path2D/PathFollow2D/Marker2D.global_position
		game_root.add_child(instance)
		enemy_count = enemy_count + 1
		
		enemies_spawned_this_wave += 1
	else:
		$SpawnTimer.stop()

func new_wave():
	print("new_wave, wave = ",wave)
	enemies_this_wave = (2*wave) + 4
	enemies_spawned_this_wave = 0
	$SpawnTimer.start()

func start_game():
	$Player.position = $Player/Path2D/PathFollow2D/Marker2D.position
	wave = 0
	enemy_count = 0
	new_wave()
	
	
func you_win():
	print("You Win!")
	
func _process(delta: float) -> void:
	pass

func check_game_state() -> void:
	# if all enemies have been defeated
	if enemies_spawned_this_wave == enemies_this_wave and enemy_count == 0:
		wave += 1
		if (wave == num_waves):
			you_win()
		else:
			new_wave()

func _on_player_colliding(colliding_body: Node2D, attacking: bool) -> void:
	print("colliding!")
	if attacking: # If the player is attacking during the collision, remove the enemy
		var enemy_node = colliding_body.get_parent()
		enemy_node.queue_free()
		enemy_count -= 1
		check_game_state()
	
