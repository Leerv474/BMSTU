import re

text = "So she was considering in her own mind, as well as she could, for the hot day made her feel very sleepy and stupid, whether the pleasure of making a daisy-chain would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her."

matches = re.findall(r'\b\w{2}', text)

print("Два первых символа каждого слова:")
for match in matches:
    print(match)
