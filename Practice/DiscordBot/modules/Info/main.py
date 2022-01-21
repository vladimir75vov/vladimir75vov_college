import os
import sys
import psutil
import datetime
import discord
import core
import config
from discord.ext import commands
from colorama import Fore, Back, Style

class modules(commands.Cog):
    def __init__(self, bot):
        self.bot = bot

    @commands.is_owner()
    @commands.command()
    async def status(self, ctx):
        try:
            ping = self.bot.latency
            ps = psutil
            embed = discord.Embed(title='Тех. сведения', color=0xff0000)
            embed.add_field(name='Использование CPU',value=f'В настоящее время используется: {ps.cpu_percent()}%',inline=True)
            embed.add_field(name='Использование RAM',value=
            f'Доступно: {ps.virtual_memory().available/1073741824:.2f} ГБ\n'
            f'Используется: {ps.virtual_memory().used/1073741824:.2f} ГБ\n'
            f'Всего: {ps.virtual_memory().total/1073741824:.2f} ГБ',inline=True)

            ping_emoji = "🟩🔳🔳🔳🔳"
            ping_list = [
                {"ping": 0.00000000000000000, "emoji": "🟩🔳🔳🔳🔳"},
                {"ping": 0.10000000000000000, "emoji": "🟧🟩🔳🔳🔳"},
                {"ping": 0.15000000000000000, "emoji": "🟥🟧🟩🔳🔳"},
                {"ping": 0.20000000000000000, "emoji": "🟥🟥🟧🟩🔳"},
                {"ping": 0.25000000000000000, "emoji": "🟥🟥🟥🟧🟩"},
                {"ping": 0.30000000000000000, "emoji": "🟥🟥🟥🟥🟧"},
                {"ping": 0.35000000000000000, "emoji": "🟥🟥🟥🟥🟥"}
            ]

            for ping_one in ping_list:
                if ping <= ping_one["ping"]:
                    ping_emoji = ping_one["emoji"]
                    break

            embed.add_field(name='Пинг Бота',
                            value=f'Пинг: {ping * 1000:.0f}ms\n'
                            f'`{ping_emoji}`',inline=True)

            for disk in ps.disk_partitions():
                usage = ps.disk_usage(disk.mountpoint)

            embed.add_field(name="‎‎‎‎ ", value=f'```{disk.device}```',
                            inline=False)
            embed.add_field(name='Всего на диске',
                            value=f'{usage.total/1073741824:.2f} ГБ', inline=True)
            embed.add_field(name='Свободное место на диске',
                            value=f'{usage.free/1073741824:.2f} ГБ', inline=True)
            embed.add_field(name='Используемое дисковое пространство',
                            value=f'{usage.used/1073741824:.2f} ГБ', inline=True)
            await ctx.send(embed=embed)
            
        except Exception as e:
            print(Fore.YELLOW + "[Log] " + Style.RESET_ALL + f"Произошла ошибка. Модуль: status\n\r{e}") 

    @commands.command()
    @commands.bot_has_permissions(manage_messages = True)
    async def bot(self, ctx):
        message = []
        jsonLang = core.langUser(ctx.author.id)
        embed = discord.Embed(title=jsonLang['bot'][0], description=f"{jsonLang['bot'][1]} {ctx.guild.name}", color = 0x4d4d4d)
        embed.add_field(name=jsonLang['bot'][2], value=ctx.guild.owner.name, inline=True)
        embed.add_field(name=jsonLang['bot'][3], value=config.version, inline=True)
        embed.add_field(name=jsonLang['bot'][4], value="1", inline=True)#%H:%M:%S 
        embed.add_field(name=jsonLang['bot'][5], value=jsonLang['bot'][6], inline=True)
        embed.add_field(name=jsonLang['bot'][7], value=jsonLang['bot'][8], inline=True)
        embed.set_footer(text=jsonLang['bot'][9])
        embed.set_thumbnail(url = self.bot.user.avatar_url)
        message.append(await ctx.send(embed=embed))
        await message[len(message)-1].add_reaction('📕')
        await message[len(message)-1].add_reaction('📘')
        await message[len(message)-1].add_reaction('📗')
        await message[len(message)-1].add_reaction('❌')
        def check(arg):
            if ctx.author.id == arg.user_id and arg.message_id == message[len(message)-1].id:
                return arg.emoji.name

        while True:
            try:
                reaction = await self.bot.wait_for('raw_reaction_add', timeout=60.0, check=check)
                await message[len(message)-1].remove_reaction(reaction.emoji.name,self.bot.get_user(reaction.user_id))
                if reaction.emoji.name == '📕':
                    print(1)
                elif reaction.emoji.name == '📘':
                    embed = discord.Embed(title=jsonLang['botServer'][0], description='', color = 0x4d4d4d)
                    embed.description=(
                        f"{jsonLang['botServer'][1]} {ctx.guild.created_at.strftime('%A, %b %#d %Y')}\n"
                        f"{jsonLang['botServer'][2]} {len(ctx.guild.roles)}\n"
                        f"{jsonLang['botServer'][3]} {ctx.guild.member_count}\n")
                    embed.add_field(name=jsonLang['botServer'][4], value=
                        f"{jsonLang['botServer'][5]} {len(list(filter(lambda x: x.status == discord.Status.online, ctx.guild.members)))}\n "+
                        f"{jsonLang['botServer'][6]} {len(list(filter(lambda x: x.status == discord.Status.idle, ctx.guild.members)))}\n"+
                        f"{jsonLang['botServer'][7]} {len(list(filter(lambda x: x.status == discord.Status.dnd, ctx.guild.members)))}\n"+
                        f"{jsonLang['botServer'][8]}{ len(list(filter(lambda x: x.status == discord.Status.offline, ctx.guild.members)))}\n", inline=True)
                    embed.add_field(name=jsonLang['botServer'][9], value=
                        f"{jsonLang['botServer'][10]} {len(ctx.guild.channels)}\n"+
                        f"{jsonLang['botServer'][11]} {len(ctx.guild.voice_channels)}\n"+
                        f"{jsonLang['botServer'][12]} {len(ctx.guild.text_channels)}\n", inline=True)
                    embed.add_field(name=jsonLang['botServer'][13], value=
                        f"{jsonLang['botServer'][14]} {ctx.guild.region}\n"
                        f"{jsonLang['botServer'][15]} {len([m for m in ctx.guild.members if m.bot])}\n"
                        f"{jsonLang['botServer'][16]} {ctx.guild.verification_level}\n", inline=True)
                    message.append(await ctx.send(embed=embed))
                    await message[len(message)-1].add_reaction('❌')
                    while True:
                        try:
                            reaction = await self.bot.wait_for('raw_reaction_add', timeout=60.0, check=check)
                            await message[len(message)-1].remove_reaction(reaction.emoji.name,self.bot.get_user(reaction.user_id))
                            
                            if reaction.emoji.name == '❌':
                                await message[len(message)-1].delete()
                                del message[len(message)-1]
                                break
                        except Exception as e:
                            break
                elif reaction.emoji.name == '❌':
                    await message[len(message)-1].delete()
                    await ctx.message.delete()
                    message.clear()
                    break
            except Exception as e:
                message.clear()
                break
    
def setup(client):
    client.add_cog(modules(client))