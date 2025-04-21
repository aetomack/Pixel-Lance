extends CharacterBody2D


const SPEED = 300.0
const JUMP_VELOCITY = -400.0
var attacking = false

signal colliding(colliding_body,attacking)


func _physics_process(delta: float) -> void:
	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var horizontal := Input.get_axis("ui_left", "ui_right")
	var vertical := Input.get_axis("ui_up","ui_down")
	if horizontal or vertical: # if moving
		var direction = Vector2(horizontal,vertical)
		direction = direction.normalized()
		velocity = direction * SPEED
		# Set animation
		if not attacking:
			$AnimatedSprite2D.animation = "moving"
			if horizontal: # change direction only if moving
				$AnimatedSprite2D.flip_h = velocity.x < 0 
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.y = move_toward(velocity.y, 0, SPEED)
		if not attacking:
			$AnimatedSprite2D.animation = "idle"
	# Attacking
	if Input.is_action_just_pressed("ui_select"):
		attack()
	
	move_and_slide()

# to use for fighting
func facing_left():
	return $AnimatedSprite2D.flip_h

func facing_right():
	return not $AnimatedSprite2D.flip_h	

func attack():
	attacking = true
	$AnimatedSprite2D.animation = "attack"
	$AttackTimer.start()



func _on_battle_box_body_entered(body: Node2D) -> void:
	if body.is_in_group("enemy"):
		# print("colliding with ",body.name)
		colliding.emit(body,attacking)
		


func _on_attack_timer_timeout() -> void:
	attacking = false
