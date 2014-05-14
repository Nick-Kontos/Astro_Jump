function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createAsteroid(300,900,0,0)
	createAsteroid(700,1200,0,0)
	
	createAsteroid(1200,600,0,0)
	createAsteroid(1970,200,0,0)
	createAsteroid(1650,1200,0,0)
	--createAsteroid(600.0,1000.0,0.0,0.0,29.0)
	--createAsteroid(900.0,500.0,0.0,0.0,29.0)
	--createAsteroid(1200.0,1000.0,0.0,0.0,29.0)
	--createAsteroid(1500.0,500.0,0.0,0.0,29.0)
	createWinAsteroid(2400,500,0,0)
	createPlatform(650,100,0,0)
	createPlatform(650,300,0,0)
	createPlatform(650,500,0,0)
	
	
	createPlatform(350,1000,0,0)
	createPlatform(350,1200,0,0)
	createPlatform(350,1400,0,0)
	createPlatform(350,1600,0,0)
	createPlatform(350,1800,0,0)
	createPlatform(350,2000,0,0)
	
	--set up player
	createPlayer(300,200,0,0)
	createEnemy(500,500,0,0,1)
	addPointToEnemy(0,1)
	addPointToEnemy(0,2)
	addPointToEnemy(0,4)
	addPointToEnemy(0,3)
	addPointToEnemy(0,1)
	addPointToEnemy(0,4)
	
	createEnemy2(1000.0,1000.0,0,0,2)
	addPointToEnemy2(0,1234,432)
	addPointToEnemy2(0,800,675)
	addPointToEnemy2(0,356,750)
	addPointToEnemy2(0,1605,1000)
	createEnemy3(1000.0, 400.0,0.0,0,.5,1000)
end