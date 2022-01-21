import os
import core
import config
import discord 
from discord.ext import commands
from colorama import Fore, Back, Style

class modules(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
    
    @commands.is_owner()
    @commands.command()
    async def load(self, ctx, extension = 'all'):
        try:
            jsonLang = core.langUser('defaultOwner')
            for file in os.listdir(f'./modules/{extension}'):
                if file.endswith('.py') and file[:-3] != '__init__':
                    self.bot.load_extension(f'modules.{extension}.{file[:-3]}')
                    print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["load"][0]} {extension}')
            if not commands.NotOwner:
                await ctx.send(jsonLang["load"][1])
            else:
                await ctx.send(f'{jsonLang["load"][2]} **{extension}** {jsonLang["load"][3]}')
        except Exception as e:
            print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["load"][4]} {extension}\n\r{e}')

    @commands.is_owner()
    @commands.command()
    async def unload(self, ctx, extension = 'all'):
        try:
            jsonLang = core.langUser('defaultOwner')
            for file in os.listdir(f'./modules/{extension}'):
                if file.endswith('.py') and file[:-3] != '__init__':
                    self.bot.unload_extension(f'modules.{extension}.{file[:-3]}')
                    print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["unload"][0]} {extension}')
            if not commands.NotOwner:
                await ctx.send(jsonLang["unload"][1])
            else:
                await ctx.send(f'{jsonLang["unload"][2]} **{extension}** {jsonLang["unload"][3]}')
        except Exception as e:
            print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["unload"][4]} {extension}\n\r{e}')
    
    @commands.is_owner()
    @commands.command()
    async def reload(self, ctx, extension = 'all'):
        try:
            jsonLang = core.langUser('defaultOwner')
            for file in os.listdir(f'./modules/{extension}'):
                if file.endswith('.py') and file[:-3] != '__init__':
                    self.bot.reload_extension(f'modules.{extension}.{file[:-3]}')
                    print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["unload"][0]} {extension}')
            if not commands.NotOwner:
                await ctx.send(jsonLang["unload"][1])
            else:
                await ctx.send(f'{jsonLang["unload"][2]} **{extension}** {jsonLang["unload"][3]}')
        except Exception as e:
            print(Fore.YELLOW + '[Log] ' + Style.RESET_ALL + f'{jsonLang["unload"][4]} {extension}\n\r{e}') 

def setup(client):
    client.add_cog(modules(client))