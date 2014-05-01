function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createAsteroid(700.0,100.0,0.0,0.0,29.0)
	createAsteroid(1700.0,500.0,0.0,0.0,29.0)
	createAsteroid(2200.0,1250.0,0.0,0.0,29.0)
	createAsteroid(1350.0,1500.0,0.0,0.0,29.0)
	createAsteroid(950.0,1300.0,0.0,0.0,29.0)
	createWinAsteroid(1700.0,1500.0,0.0,0.0,29.0)
	
	--set up player
	createPlayer(300.0,200.0,0,0,4.0)
	createEnemy(500.0,500.0,0,0,4.0)
end