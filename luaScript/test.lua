wave1 = startEnemySettings()

group = glueAddEnemyGroup(wave1)

glueSetEnemyCount(group,10)
glueSetDelayFrame(group,1)
glueSetLuaScript(group,"C:/Users/sugiyama/Documents/InvaderGame/luaScript/coroutine.lua")
glueSetImage(group,NormalEnemy)
glueSetInitPos(group, 100.0,100.0)
glueSetSpeed(group,0.1,0.1)
glueSetHP(group,1)
glueSetTexScale(group,0.1)
glueSetBulletStatus(group,0.0,1.0,4.0,2.0,4.0,255.0,255.0,255.0,10.0)
glueSetBulletLimit(group,10)



group2 = glueAddEnemyGroup(wave1)

glueSetEnemyCount(group2,10)
glueSetDelayFrame(group2,1)
glueSetLuaScript(group2,"C:/Users/sugiyama/Documents/InvaderGame/luaScript/coroutine.lua")
glueSetImage(group2,NormalEnemy)
glueSetInitPos(group2, 100.0,100.0)
glueSetSpeed(group2,0.5,0.5)
glueSetHP(group2,1)
glueSetTexScale(group2,0.1)
glueSetBulletStatus(group2,0.0,1.0,4.0,2.0,4.0,255.0,255.0,255.0,10.0)
glueSetBulletLimit(group2,10)






glueSetImage(Player,BossEnemy)
glueSetTexScale(Player,0.1)
glueSetBulletStatus(Player,0.0,-1.0,1.0,3.0,10.0,255.0,0.0,255.0,0.2)
glueSetBulletLimit(Player,10)

print("A")