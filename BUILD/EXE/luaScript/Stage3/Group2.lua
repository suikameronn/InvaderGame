function Update()
    if Index == 0 then
        while true do
            glueSetMove(myEnemy,0,20)
            coroutine.yield()
            glueSetMove(myEnemy,SCREEN_WIDTH - TEX_WIDTH,20)
            coroutine.yield()
        end
    else
        while true do
            glueSetMove(myEnemy,SCREEN_WIDTH - TEX_WIDTH,20)
            coroutine.yield()
            glueSetMove(myEnemy,0,20)
            coroutine.yield()
        end
    end
end