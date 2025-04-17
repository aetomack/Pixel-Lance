extends Node2D
@onready var game_root: Node2D = $"."

var enemy := preload("res://scenes/enemy.tscn")
@onready var path_follow_2d: PathFollow2D = $Player/Path2D/PathFollow2D
var wave = 0
var enemy_count = 0
var max_enemy

func _ready():
	var instance = enemy.instantiate()
	add_child(instance)
	max_enemy = (2*wave) + 4
	
func _on_spawn_timer_timeout() -> void:
	while(enemy_count < max_enemy):
		var rng = RandomNumberGenerator.new()
		
		rng.randomize
		path_follow_2d.progress = rng.randi_range(0,3664)
		var instance = enemy.instantiate()
		
		instance.position = $Player/Path2D/PathFollow2D/Marker2D.global_position
		game_root.add_child(instance)
		enemy_count = enemy_count + 1
	wave+=1
	
	
