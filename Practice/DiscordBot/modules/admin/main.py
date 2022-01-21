import os
import core
import config
import discord 
from discord.ext import commands
from colorama import Fore, Back, Style

localConfig = {
    "test":"1"
}

class modules(commands.Cog):
    def __init__(self, bot):
        self.bot = bot

        

def setup(client):
    client.add_cog(modules(client))