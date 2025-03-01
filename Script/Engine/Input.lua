-- define module table
local LTBInput = {}

-- check mouse input
function LTBInput.IsKeyPressed(button)
    -- print("pressed!")
    return ApiKeyPressed(button)  
end

-- check key input
function LTBInput.IsKeyDown(key)    
    return ApiKeyDown(key)
end

-- mouse input codes  
LTBInput.MOUSE_LEFT     = 0
LTBInput.MOUSE_MIDDLE   = 1
LTBInput.MOUSE_RIGHT    = 2
LTBInput.MOUSE_BUTTON_4 = 3
LTBInput.MOUSE_BUTTON_5 = 4
LTBInput.MOUSE_BUTTON_6 = 5
LTBInput.MOUSE_BUTTON_7 = 6
LTBInput.MOUSE_BUTTON_8 = 7

-- key input codes
LTBInput.KEY_SPACE             = 32
LTBInput.KEY_APOSTROPHE        = 39 
LTBInput.KEY_COMMA             = 44 
LTBInput.KEY_MINUS             = 45  
LTBInput.KEY_PERIOD            = 46  
LTBInput.KEY_SLASH             = 47  
LTBInput.KEY_0                 = 48
LTBInput.KEY_1                 = 49
LTBInput.KEY_2                 = 50
LTBInput.KEY_3                 = 51
LTBInput.KEY_4                 = 52
LTBInput.KEY_5                 = 53
LTBInput.KEY_6                 = 54
LTBInput.KEY_7                 = 55
LTBInput.KEY_8                 = 56
LTBInput.KEY_9                 = 57
LTBInput.KEY_SEMICOLON         = 59  
LTBInput.KEY_EQUAL             = 61  
LTBInput.KEY_A                 = 65
LTBInput.KEY_B                 = 66
LTBInput.KEY_C                 = 67
LTBInput.KEY_D                 = 68
LTBInput.KEY_E                 = 69
LTBInput.KEY_F                 = 70
LTBInput.KEY_G                 = 71
LTBInput.KEY_H                 = 72
LTBInput.KEY_I                 = 73
LTBInput.KEY_J                 = 74
LTBInput.KEY_K                 = 75
LTBInput.KEY_L                 = 76
LTBInput.KEY_M                 = 77
LTBInput.KEY_N                 = 78
LTBInput.KEY_O                 = 79
LTBInput.KEY_P                 = 80
LTBInput.KEY_Q                 = 81
LTBInput.KEY_R                 = 82
LTBInput.KEY_S                 = 83
LTBInput.KEY_T                 = 84
LTBInput.KEY_U                 = 85
LTBInput.KEY_V                 = 86
LTBInput.KEY_W                 = 87
LTBInput.KEY_X                 = 88
LTBInput.KEY_Y                 = 89
LTBInput.KEY_Z                 = 90
LTBInput.KEY_LEFT_BRACKET      = 91   
LTBInput.KEY_BACKSLASH         = 92   
LTBInput.KEY_RIGHT_BRACKET     = 93   
LTBInput.KEY_GRAVE_ACCENT      = 96   
LTBInput.KEY_WORLD_1           = 161  
LTBInput.KEY_WORLD_2           = 162  

-- Fion keys *--
LTBInput.KEY_ESCAPE            = 256
LTBInput.KEY_ENTER             = 257
LTBInput.KEY_TAB               = 258
LTBInput.KEY_BACKSPACE         = 259
LTBInput.KEY_INSERT            = 260
LTBInput.KEY_DELETE            = 261
LTBInput.KEY_RIGHT             = 262
LTBInput.KEY_LEFT              = 263
LTBInput.KEY_DOWN              = 264
LTBInput.KEY_UP                = 265
LTBInput.KEY_PAGE_UP           = 266
LTBInput.KEY_PAGE_DOWN         = 267
LTBInput.KEY_HOME              = 268
LTBInput.KEY_END               = 269
LTBInput.KEY_CAPS_LOCK         = 280
LTBInput.KEY_SCROLL_LOCK       = 281
LTBInput.KEY_NUM_LOCK          = 282
LTBInput.KEY_PRINT_SCREEN      = 283
LTBInput.KEY_PAUSE             = 284
LTBInput.KEY_F1                = 290
LTBInput.KEY_F2                = 291
LTBInput.KEY_F3                = 292
LTBInput.KEY_F4                = 293
LTBInput.KEY_F5                = 294
LTBInput.KEY_F6                = 295
LTBInput.KEY_F7                = 296
LTBInput.KEY_F8                = 297
LTBInput.KEY_F9                = 298
LTBInput.KEY_F10               = 299
LTBInput.KEY_F11               = 300
LTBInput.KEY_F12               = 301
LTBInput.KEY_F13               = 302
LTBInput.KEY_F14               = 303
LTBInput.KEY_F15               = 304
LTBInput.KEY_F16               = 305
LTBInput.KEY_F17               = 306
LTBInput.KEY_F18               = 307
LTBInput.KEY_F19               = 308
LTBInput.KEY_F20               = 309
LTBInput.KEY_F21               = 310
LTBInput.KEY_F22               = 311
LTBInput.KEY_F23               = 312
LTBInput.KEY_F24               = 313
LTBInput.KEY_F25               = 314
LTBInput.KEY_KP_0              = 320
LTBInput.KEY_KP_1              = 321
LTBInput.KEY_KP_2              = 322
LTBInput.KEY_KP_3              = 323
LTBInput.KEY_KP_4              = 324
LTBInput.KEY_KP_5              = 325
LTBInput.KEY_KP_6              = 326
LTBInput.KEY_KP_7              = 327
LTBInput.KEY_KP_8              = 328
LTBInput.KEY_KP_9              = 329
LTBInput.KEY_KP_DECIMAL        = 330
LTBInput.KEY_KP_DIVIDE         = 331
LTBInput.KEY_KP_MULTIPLY       = 332
LTBInput.KEY_KP_SUBTRACT       = 333
LTBInput.KEY_KP_ADD            = 334
LTBInput.KEY_KP_ENTER          = 335
LTBInput.KEY_KP_EQUAL          = 336
LTBInput.KEY_LEFT_SHIFT        = 340
LTBInput.KEY_LEFT_CONTROL      = 341
LTBInput.KEY_LEFT_ALT          = 342
LTBInput.KEY_LEFT_SUPER        = 343
LTBInput.KEY_RIGHT_SHIFT       = 344
LTBInput.KEY_RIGHT_CONTROL     = 345
LTBInput.KEY_RIGHT_ALT         = 346
LTBInput.KEY_RIGHT_SUPER       = 347
LTBInput.KEY_MENU              = 348

-- export module
return LTBInput
