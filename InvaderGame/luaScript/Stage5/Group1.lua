function Update()
    while true do
        glueSetMove(myEnemy,0,20)
        coroutine.yield()
        glueSetMove(myEnemy,SCREEN_WIDTH - TEX_WIDTH,20)
        coroutine.yield()
        glueSetMove(myEnemy,100,100)
        coroutine.yield()
    end
end