extends CharacterBody2D


const SPEED = 300.0
const JUMP_VELOCITY = -400.0
var attacking = false
var health: int = 5 # Start with 5 health
enum PlayerState { ALIVE, DEAD }
var state: PlayerState = PlayerState.ALIVE
var score: int = 0


signal colliding(colliding_body,attacking)
signal took_damage(amount)


func _physics_process(delta: float) -> void:
	if state == PlayerState.DEAD:
		return
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
	if state == PlayerState.DEAD:
		return
	if body.is_in_group("enemy"):
		# print("colliding with ",body.name)
		colliding.emit(body,attacking)
		score += 1
		update_score_ui()
		if not attacking:
			take_damage(1)
			score -= 1
			update_score_ui() # Take 1 damage if hit and not attacking
		

func _on_attack_timer_timeout() -> void:
	attacking = false
	
func take_damage(amount: int) -> void:
	if state == PlayerState.DEAD:
		return
	health -= amount
	took_damage.emit(amount)
	update_health_ui()
	print("Ouch! Health is now ", health)

	if health <= 0:
		die()
		
func update_health_ui() -> void:
	var health_bar = get_parent().get_node("UI/HealthBar")
	health_bar.value = health
func update_score_ui() -> void:
	var ui = get_parent().get_node("UI")
	if ui:
		var score_label = ui.get_node("ScoreLabel")  # Make sure ScoreLabel is named correctly
		if score_label:
			score_label.text = "Score: " + str(score)  # Update the text to show the score
		else:
			print("ScoreLabel node not found!")
func die() -> void:
	if state == PlayerState.DEAD:
		return
	state = PlayerState.DEAD
	print("Player is dead!")

	# Stop BattleBox and AttackTimer
	if $BattleBox:
		$BattleBox.set_deferred("monitoring", false)
	if $AttackTimer:
		$AttackTimer.stop()


	# Tell GameManager or Game node to handle death
	get_parent().call_deferred("on_player_death", self)
