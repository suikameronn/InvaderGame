selectText = glueCreateText()
glueSetFont(selectText,Big)
glueSetColor(selectText,255,255,255)
glueSetPos(selectText,81,70)
glueSetText(selectText,"CourseSelect")

back = glueCreateButton()
glueSetPos(back,10,600)
glueSetOffset(back,50,30)
glueSetText(back,"Back")
glueSetLabelColor(back,0,0,0)
glueSetFont(back,Small)
glueSetLabelTextSize(back,14)
glueSetNextScene(back,1,"luaScript/Title.lua")

panel = glueCreateScrollPanel()
glueSetPos(panel,100,150)
glueSetPanelSize(panel,300,450)
glueSetColor(panel,255,255,255)
glueSetScrollSpeed(panel,50.0)
glueSetScrollLimit(panel,50,0)

for i = 1 , 5 do
    stageSelect = glueCreateButtonToPanel(panel)
    glueSetPos(stageSelect,50, 5 + (i - 1) * 150)
    glueSetText(stageSelect,i)
    glueSetOffset(stageSelect,200,100)
    glueSetLabelColor(stageSelect,255,255,255)
    glueSetFont(stageSelect,Normal)
    glueSetLabelTextSize(stageSelect,28)
    glueSetNextScene(stageSelect,2,"luaScript/Stage" .. i .. "/Stage.lua")
end