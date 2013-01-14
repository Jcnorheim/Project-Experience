using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Petio.RandomStory
{
    public class RandomStory
    {
        private Random r = new Random();
        private List<string> m_Advice;
        public RandomStory()
        {
            m_Advice = new List<string>();
            m_Advice.Add("Somewhere near a man has just taken his last breath. His eyes are still open!");
            m_Advice.Add("The plague swept through here. There are rooms they have yet to clean.");
            m_Advice.Add("The crushed minerals, the farm animals, the vials of liquid mysteries - all these and more are necessary for his experiments.");
            m_Advice.Add("He walks the floor, careful to touch each stone only once, counting. He cannot purge his mind of the thoughts.");
            m_Advice.Add("When the sea wall broke, many strange things were drowned and forgotten.");
        }
        public string GetAdvice()
        {
            string randomAdvice = m_Advice.ElementAt(r.Next(m_Advice.Count));
            return randomAdvice;
        }
    }
}