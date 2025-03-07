function Update()
    while true do
        glueSetMove(myEnemy,10 + Index * 100,20 + Index * 80)
        coroutine.yield()
        glueSetMove(myEnemy,10,20 + Index * 80)
        coroutine.yield()
    end
end