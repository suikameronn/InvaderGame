text = glueCreateText()
glueSetColor(text,255,0,0)
glueSetPos(text,113,70)
glueSetText(text,"GameOver")
glueSetFont(text,Big)

button = glueCreateButton()
glueSetPos(button,100,390)
glueSetText(button,"StageSelect")
glueSetLabelOffset(button,300,80)
glueSetLabelColor(button,255,255,255)
glueSetFont(button,Normal)
glueSetLabelTextSize(button,28)
glueSetNextScene(button,1,"luaScript/CourseSelect.lua")