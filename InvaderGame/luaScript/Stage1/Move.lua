function Update()
    while true do
        glueSetMove(myEnemy,20, Index * 70 + 10)
        coroutine.yield()
        glueSetMove(myEnemy,400,Index * 70 + 10)
        coroutine.yield()
    end
end