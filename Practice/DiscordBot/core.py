import os
import sys
import discord
from discord.ext import commands
import config
import inspect

from colorama import Fore, Back, Style

import sqlite3
import json

prefix = config.prefix
status = config.status

bot = commands.Bot(command_prefix=prefix)
bot.remove_command("help")

@bot.event
async def on_ready():
    print(" ")
    print(Fore.CYAN + "===================================" + Style.RESET_ALL)
    print(f'          Смена статуса...   ')
    await bot.change_presence(activity=discord.Game(name=status))
    print(f'          Бот запущен!           ')
    print(Fore.CYAN + "===================================" + Style.RESET_ALL)
    print(f'  Статус   - {status}          ')
    print(f'  Имя бота - {bot.user.name}')
    print(f'  ID бота  - {bot.user.id}  ')
    print(Fore.CYAN + "===================================" + Style.RESET_ALL)

for nameModule in os.listdir("./modules"):
    if nameModule[:-3] != "__init__":
        for file in os.listdir(f"./modules/{nameModule}"):
            if file.endswith(".py") and file[:-3] != "__init__":
                bot.load_extension(f"modules.{nameModule}.{file[:-3]}")
                print(Fore.YELLOW + "[Log] " + Style.RESET_ALL + f"Загружен модуль - {nameModule}") 

def dataBase(request):
    try:
        dataBase = sqlite3.connect("database.sqlite3")
        sql = dataBase.cursor()
        sql.execute(request)
        dataBaseReturn = sql.fetchone()
    except Exception as e:
        print(Fore.YELLOW + "[Log] " + Style.RESET_ALL + f"Произошла ошибка. Функция: langUser\n\rRequest: {request}\n\r{e}")
    finally:
        dataBase.close()
    return dataBaseReturn

def langUser(request):
    try:
        requestDataBase = dataBase(f"SELECT * FROM settingUser WHERE userid = '{request}'")
        current_frame = inspect.currentframe()
        caller_frame = current_frame.f_back
        code_obj = caller_frame.f_code
        with open(f"{os.path.dirname(code_obj.co_filename)}\language\{requestDataBase[2]}.json", "r", encoding="utf-8") as read_file:
            langUserReturn = json.load(read_file)
    except Exception as e:
        print(Fore.YELLOW + "[Log] " + Style.RESET_ALL + f"Произошла ошибка. Функция: langUser\n\rRequest: {request}\n\r{e}")
    return langUserReturn

bot.run(config.token["discord"])