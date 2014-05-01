function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createAsteroid(700.0,100.0,0.0,0.0,29.0)
	createAsteroid(700.0,725.0,0.0,0.0,29.0)
	createAsteroid(1500.0,900.0,0.0,0.0,29.0)
	createAsteroid(2000.0,1500.0,0.0,0.0,29.0)
	createAsteroid(1250.0,800.0,0.0,0.0,29.0)
	createAsteroid(2500.0,1100.0,0.0,0.0,29.0)
	
	--set up player
	createPlayer(300.0,200.0,0,0,4.0)
	createEnemy(500.0,500.0,0,0,4.0)
end