function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createAsteroid(300.0,500.0,0.0,0.0,29.0)
	createAsteroid(600.0,1000.0,0.0,0.0,29.0)
	createAsteroid(900.0,500.0,0.0,0.0,29.0)
	createAsteroid(1200.0,1000.0,0.0,0.0,29.0)
	createAsteroid(1500.0,500.0,0.0,0.0,29.0)
	createWinAsteroid(1800.0,1000.0,0.0,0.0,29.0)
	
	--set up player
	createPlayer(300.0,200.0,0,0,4.0)
	createEnemy(500.0,500.0,0,0,4.0)
	
	--add platform
	createPlatform(400.0,800.0,0.0,0.0,29.0)
end