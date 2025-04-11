  def countSymmetricIntegers(self, low, high):
        count = 0

        for i in range(low, high + 1):
            s = str(i)
            if len(s) % 2 == 0:  # only consider numbers with even length
                mid = len(s) // 2
                first_part = s[:mid]
                second_part = s[mid:]
                if sum(int(c) for c in first_part) == sum(int(c) for c in     second_part):
                    count += 1

        return count