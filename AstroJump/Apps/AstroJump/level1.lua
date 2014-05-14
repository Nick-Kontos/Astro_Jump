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
	createEnemy(500.0,500.0,0,0,4.0,1)
	addPointToEnemy(0,1)
	addPointToEnemy(0,2)
	addPointToEnemy(0,3)
	createEnemy2(1000.0,1000.0,0,0,4.0,2)
	addPointToEnemy2(0,500,500)
	addPointToEnemy2(0,2000,2000)
	addPointToEnemy2(0,750,750)
	createEnemy3(2000.0, 2000.0,0.0,0,4.0,.5)
end