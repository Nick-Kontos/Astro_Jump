function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createAsteroid(700.0,100.0,0.0,0.0,29.0)
	createAsteroid(120.0,765.0,0.0,0.0,29.0)
	createAsteroid(1800.0,900.0,0.0,0.0,29.0)
	createWinAsteroid(2500.0,500.0,0.0,0.0,29.0)
	createAsteroid(1250.0,800.0,0.0,0.0,29.0)
	createAsteroid(800.0,1100.0,0.0,0.0,29.0)
	
	--set up player
	createPlayer(2000.0,200.0,0,0,4.0)
	createEnemy(500.0,500.0,0,0,4.0)
	createEnemy(500.0,500.0,0,0,4.0)
end