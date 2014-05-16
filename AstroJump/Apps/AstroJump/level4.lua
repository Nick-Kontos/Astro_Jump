function levela()
	--set gravity
	setGravity(0.0)
	--set up asteroids
	createWinAsteroid(3000,100,0,0)
	createAsteroid(100,200,0,0)
	createPowerUp(100,200,1,-1)
	createAsteroid(400,200,0,0)
	--Portal 0
	createPowerUp(400,200,3,0)
	createAsteroid(50,1600,0,0)
	createPowerUp(50,1600,2,-1)
	createAsteroid(1000,1600,0,0)
	createAsteroid(2600,1800,0,0)
	--Portal 1
	createPowerUp(2600,1800,3,1)
	createAsteroid(2900,1550,0,0)
	--Portal 2
	createPowerUp(50,1600,3,2)
	createPlatform(150,1650,0,0)
	createPlatform(150,1850,0,0)
	createPlatform(150,2050,0,0)
	createBlackHole(2300,1600,3)
	createBlackHole(2200,1400,3)
	
	--bots/players/etc
	createPlayer(250,1750,0,0)
	createEnemy2(3000,200,0,0,1)
	addPointToEnemy2(0,3000,200)
	addPointToEnemy2(0,2600,200)
	createEnemy2(3000,400,0,0,1)
	addPointToEnemy2(1,3000,400)
	addPointToEnemy2(1,2600,400)
	createEnemy2(3000,600,0,0,1)
	addPointToEnemy2(2,3000,600)
	addPointToEnemy2(2,2600,600)
	createEnemy2(3000,800,0,0,1)
	addPointToEnemy2(3,3000,800)
	addPointToEnemy2(3,2600,800)
	createEnemy2(350,1800,0,0,1)
	addPointToEnemy2(4,350,1800)
	addPointToEnemy2(4,500,1500)
	createEnemy2(500,1800,0,0,.5)
	addPointToEnemy2(5,500,1800)
	addPointToEnemy2(5,350,1500)
	
end