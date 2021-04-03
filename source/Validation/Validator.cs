using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Validation
{
    public class Validator
    {
        public IEnumerable<IRule> Rules => _Rules.AsReadOnly();
        private readonly List<IRule> _Rules = new();
        private readonly HashSet<RuleKey> _RuleKeys = new();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="rule"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(IRule rule)
        {
            lock (this)
            {
                var ruleKey = new RuleKey { Realm = rule.Realm, Code = rule.Code };
                if (_RuleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(rule.Realm, rule.Code);
                }
                this._Rules.Add(rule);
                this._RuleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="realm"></param>
        /// <param name="code"></param>
        /// <param name="severity"></param>
        /// <param name="func"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(string realm, int code, ESeverity severity, Func<Parsing.Parser, IEnumerable<Hint>> func)
        {
            lock (this)
            {
                var ruleKey = new RuleKey { Realm = realm, Code = code };
                if (_RuleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(realm, code);
                }
                this._Rules.Add(new Rule { Realm = realm, Severity = severity, Code = code, ValidationFunc = func });
                this._RuleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="realm"></param>
        /// <param name="severity"></param>
        /// <param name="func"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(string realm, ESeverity severity, Func<Parsing.Parser, IEnumerable<Hint>> func)
        {
            lock (this)
            {
                var code = (this.Rules.Any() ? this.Rules.Where((q) => q.Realm == realm).Max((q) => q.Code) : 0) + 1;
                var ruleKey = new RuleKey { Realm = realm, Code = code };
                if (_RuleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(realm, code);
                }
                this._Rules.Add(new Rule { Realm = realm, Severity = severity, Code = code, ValidationFunc = func });
                this._RuleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// Performs the validation by evaluating every <see cref="IRule"/> registered.
        /// </summary>
        /// <param name="parser"></param>
        /// <param name="reportCallback">A callback for the <see cref="IRule"/>s evaluating to false.</param>
        /// <returns>True if no <see cref="IRule"/> with a <see cref="IRule.Severity"/> of <see cref="ESeverity.Error"/> evaluated to false.</returns>
        public bool Validate(Parsing.Parser parser, Action<IRule, Hint> reportCallback)
        {
            bool success = true;
            foreach (var rule in this._Rules)
            {
                foreach (var hint in rule.IsValid(parser))
                {
                    if (rule.Severity == ESeverity.Error)
                    {
                        success = false;
                    }
                    reportCallback(rule, hint);
                }
            }
            return success;
        }
    }
}
