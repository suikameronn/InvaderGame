function Update()
    while true do
        glueSetMove(myEnemy,0,20)
        coroutine.yield()
        glueSetMove(myEnemy,435,20)
        coroutine.yield()
    end
end