import re

text = "So she was considering in her own mind, as well as she could, for the hot day made her feel very sleepy and stupid, whether the pleasure of making a daisy-chain would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her."

text = text.lower()

words = re.findall(r'\b\w+\b', text)

consonant_count = sum(1 for word in words if word[0] not in "aeiou")

words_with_repeated_letters = [(i + 1, word) for i, word in enumerate(words) if re.search(r'(.)\1', word)]

sorted_words = sorted(words)

print(f"Число слов, начинающихся с согласной: {consonant_count}")
print("Слова с одинаковыми буквами подряд и их номера:")
for idx, word in words_with_repeated_letters:
    print(f"{idx}. {word}")
print("Слова в алфавитном порядке:")
for word in sorted_words:
    print(word)
