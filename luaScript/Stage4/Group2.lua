function Update()
    while true do
        glueSetMove(myEnemy,0,20)
        coroutine.yield()
        glueSetMove(myEnemy,SCREEN_WIDTH - TEX_WIDTH,20)
        coroutine.yield()
        glueSetMove(myEnemy,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2)
        coroutine.yield()
    end
end