wave1 = startEnemySettings()
group = glueAddEnemyGroup(wave1)

glueSetEnemyCount(group,5)
glueSetLuaScript(group,"luaScript/Stage2/Group1.lua")
glueSetImage(group,NormalEnemy)
glueSetInitPos(group, 150.0,80.0)
glueSetSpeed(group,0.1,0.1)
glueSetHP(group,1)
glueSetTexScale(group,0.1)
glueAddBulletDir(group,0.0,1.0)
glueSetBulletSpeed(group,0.1)
glueSetBulletTexture(group,RedBullet,1.0)
glueSetBulletRate(group,1.0)

wave2 = startEnemySettings()
group2 = glueAddEnemyGroup(wave2)

glueSetEnemyCount(group2,5)
glueSetDelayFrame(group2,1000)
glueSetLuaScript(group2,"luaScript/Stage2/Group2.lua")
glueSetImage(group2,NormalEnemy)
glueSetInitPos(group2, 100.0,100.0)
glueSetSpeed(group2,0.05,0.05)
glueSetHP(group2,1)
glueSetTexScale(group2,0.1)
glueAddBulletDir(group2,0.0,1.0)
glueSetBulletSpeed(group2,0.2)
glueSetBulletTexture(group2,RedBullet,1.0)
glueSetBulletRate(group2,3.0)

wave3 = startEnemySettings()
group3 = glueAddEnemyGroup(wave3)

glueSetEnemyCount(group3,5)
glueSetDelayFrame(group3,1000)
glueSetLuaScript(group3,"luaScript/Stage2/Group3.lua")
glueSetImage(group3,NormalEnemy)
glueSetInitPos(group3, 100.0,100.0)
glueSetSpeed(group3,0.1,0.1)
glueSetHP(group3,1)
glueSetTexScale(group3,0.1)
glueAddBulletDir(group3,0.0,1.0)
glueSetBulletSpeed(group3,0.2)
glueSetBulletTexture(group3,RedBullet,1.0)
glueSetBulletRate(group3,0.7)

glueSetImage(Player,BossEnemy)
glueSetTexScale(Player,0.1)
glueSetBulletTexture(Player,BlueBullet,1.0)
glueAddBulletDir(Player,0.0,-1.0)
glueSetBulletSpeed(Player,0.7)
glueSetBulletRate(Player,0.2)
glueSetHP(Player,3)