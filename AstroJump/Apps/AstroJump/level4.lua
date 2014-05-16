function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createWinAsteroid(3000,100,0,0)
	createAsteroid(100,200,0,0)
	createPowerUp(100,200,1,-1)
	createAsteroid(400,400,0,0)
	--Portal 0
	createPowerUp(400,400,3,0)
	createAsteroid(50,1600,0,0)
	createPowerUp(50,1600,2,-1)
	createAsteroid(1000,1000,0,0)
	createAsteroid(2600,1800,0,0)
	--Portal 1
	createPowerUp(2600,1800,3,1)
	createAsteroid(2900,1150,0,0)
	--Portal 2
	createPowerUp(50,1600,3,2)
	createPlatform(500,1650,0,0)
	createPlatform(500,1850,0,0)
	createPlatform(500,2050,0,0)
	createPlatform(500,1450,0,0)
	createPlatform(500,1250,0,0)
	createBlackHole(2000,1600,3)
	createBlackHole(1900,700,3)
	
	--bots/players/etc
	createPlayer(700,1750,0,0)
	createEnemy2(3000,200,0,0,1)
	addPointToEnemy2(0,3000,200)
	addPointToEnemy2(0,2600,200)
	createEnemy2(3000,400,0,0,2)
	addPointToEnemy2(1,3000,400)
	addPointToEnemy2(1,2600,400)
	createEnemy2(3000,600,0,0,1)
	addPointToEnemy2(2,3000,600)
	addPointToEnemy2(2,2600,600)
	createEnemy2(3000,800,0,0,2)
	addPointToEnemy2(3,3000,800)
	addPointToEnemy2(3,2600,800)
	createEnemy2(1300,1800,0,0,1)
	addPointToEnemy2(4,1300,1800)
	addPointToEnemy2(4,1600,1700)
	createEnemy2(1500,1800,0,0,1)
	addPointToEnemy2(5,1500,1800)
	addPointToEnemy2(5,1100,1200)
	
end